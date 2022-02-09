/* c standard library headers */
#include <stdio.h>
#include <stdbool.h>

/* project headers */
#include "context.h"
#include "world.h"

/* TODO remove these */
#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>

/* the entry point of the program */
void main () {

    /* the global context object we will use instead of global variables */
    context_t context;

    ///* the state of the game world */
    world_t world;

    /* reset the gpu before doing anything else  */
    ResetGraph (0);

    /* greet the serial console hehe */
    printf ("hewwo fewwo's , welcome to the project template demo ! :3\n");

    /* initialize the context with default values */
    context_init (&context);

    /* switch the hardware state to the context */
    context_switch (&context);

    /* initialize the world state */
    world_init (&world);
    
    /* enter the main loop */
    while (true) {

        ///* draw the current state of the game world for this frame */
        world_draw (&world, &context);

        ///* update world state for the frame after that */
        world_update (&world, &context);

        /* this will send the primitive packet stream prepared in the above
         * draw function call and leave us ready to prepare the next stream */
        context_flip (&context);
    }
}
