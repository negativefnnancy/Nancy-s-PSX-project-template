#ifndef DISPLAY_H
#define DISPLAY_H

/* c standard library headers */
#include <stddef.h>

/* psy-q library headers */
#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>

/* project headers */
#include "config.h"

/* we will define a display context that encapsulates 
 * drawing environment, display environment, and deals with double buffering */
/* TODO: this is currently assuming low res progressive mode,
 * i want to be able to handle interlacing modes too */
typedef struct display_context_t {

    /* TODO re-engineer display context to allow for any number of buffers
     * not just double buffering, although make sure it doesnt introduce any
     * unnecessary overhead yeah XD */

    DRAWENV drawing_environments[N_GRAPHICS_BUFFERS];
    DISPENV display_environments[N_GRAPHICS_BUFFERS];

    /* keeps track of the state of the alternating buffers */
    size_t i_buffer;

} display_context_t;

/* initialize the display context
 * this only initializes the struct, it doesnt configure hardware state */
void display_context_init (display_context_t *context);

/* configure hardware state to reflect the given display context */
void display_context_switch (display_context_t *context);

/* swap buffers, causing the just drawn image to be displayed
 * and setting the new draw area to the old area now off screen
 * this function also waits for vblank, so this function will
 * sync the main loop with the refresh rate
 * so basically this is the function u call at the end of the main loop */
void display_context_flip (display_context_t *context);

#endif /* DISPLAY_H */
