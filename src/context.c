#include "context.h"
#include "config.h"

void context_init (context_t *context) {
  
    /* setup the display environment */
    display_context_init (&context->display);

    /* setup the graphics environment */
    graphics_context_init (&context->graphics);
}

void context_switch (context_t *context) {

    /* switch the display context */
    display_context_switch (&context->display);

    /* switch the graphics context */
    graphics_context_switch (&context->graphics);
}

void context_flip (context_t *context) {

    /* there is a three stage pipeline setup between the video encoder, the
     * gpu, and the cpu: we set it up so that the video encoder can be
     * outputting a frame while the gpu is drawing the next frame while the
     * cpu is compiling the packets for yet the next frame! */

    /* flip the display context, causing the previously rendered frame to be
     * displayed, while the other buffer will be left for us to draw to in the
     * mean time*/
    display_context_flip (&context->display);

    /* flip the graphics context, causing the previously prepared stream of
     * primitive packets to be sent to the gpu, leaving the other buffer
     * for us to prepare the next frame */
    graphics_context_flip (&context->graphics);
}

u_char *context_allocate_primitive (context_t *context, size_t size) {

    return graphics_context_allocate_primitive (&context->graphics, size);
}
