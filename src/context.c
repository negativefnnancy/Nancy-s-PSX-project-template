#include "context.h"
#include "config.h"

void context_switch (context_t *context) {

    /* switch the display context */
    display_context_switch (&context->display);

    /* initialize the gte */
    InitGeom (); /* this resets the gte */
    SetGeomOffset (CENTER_X, CENTER_Y); /* this gets added to the output of
                                           screen projection functions
                                           and contributes to our setup for
                                           properly converting from normalized
                                           device coordinates to screen
                                           coordinates */
    SetGeomScreen (SCREEN_Z); /* this sets the value that is used by the gte
                                 perspective projection functions */

    /* TODO: any particular values here that might change between contexts
     * should be stored instead as fields in context */
}

void context_init (context_t *context) {

    /* setup the display environment */
    display_context_init (&context->display);
}
