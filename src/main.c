/* c standard library headers */
#include <stdio.h>
#include <stdbool.h>

/* psy-q library headers */
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libapi.h>

/* project headers */
#include "context.h"

/* the entry point of the program */
void main () {

    /* the global context object we will use instead of global variables */
    context_t context;

    /* initialize the context with default values */
    context_init (&context);

    /* switch the hardware state to the context */
    context_switch (&context);
    
    /* enter the main loop */
    while (true) {

        display_context_flip (&context.display);
    }
}
