#ifndef CONTEXT_H
#define CONTEXT_H

#include <sys/types.h>

#include "display.h"
#include "graphics.h"

/* we will use this structure to encapsulate the hardware state of our
 * running program, this way we can stay more organized than we would using
 * global variables, and it means we can switch between multiple contexts */
typedef struct context_t {

    /* the current state of the display will be managed by this object */
    display_context_t display;

    /* the current state of the graphics (including gte state)
     * will be managed by this object */
    graphics_context_t graphics;

    /* buffers to store the states of the gamepads */
    u_char pad_buffers[N_PAD_BUFFERS][PAD_BUFFER_SIZE];

} context_t;

/* initialize a context */
void context_init (context_t *context);

/* switch program context
 * this sets the hardware state to whats described by the state of the context */
void context_switch (context_t *context);

/* flip the double buffering setup
 * this flips the display context and then the graphics context */
void context_flip (context_t *context);

/* allocate space from the current primitive buffer in the graphics context */
u_char *context_allocate_primitive (context_t *context, size_t size);

#endif /* CONTEXT_H */
