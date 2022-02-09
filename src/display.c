#include <stdbool.h>

#include "display.h"

void display_context_init (display_context_t *context) {

    /* setup the drawing environments */
    SetDefDrawEnv (&context->drawing_environments[0],
                   VRAM_BUFFER_1_X,
                   VRAM_BUFFER_1_Y,
                   RESOLUTION_X,
                   RESOLUTION_Y);
    SetDefDrawEnv (&context->drawing_environments[1],
                   VRAM_BUFFER_2_X,
                   VRAM_BUFFER_2_Y,
                   RESOLUTION_X,
                   RESOLUTION_Y);

    /* setup the display environments
     * they will be in the oppsition positions in vram as the corresponding
     * drawing environments because in the double buffering setup the drawing
     * will happen on one buffer while the display happens on the other */
    SetDefDispEnv (&context->display_environments[0],
                   VRAM_BUFFER_2_X,
                   VRAM_BUFFER_2_Y,
                   RESOLUTION_X,
                   RESOLUTION_Y);
    SetDefDispEnv (&context->display_environments[1],
                   VRAM_BUFFER_1_X,
                   VRAM_BUFFER_1_Y,
                   RESOLUTION_X,
                   RESOLUTION_Y);

    /* set the automatic background clear color for the drawing environments
     * this will cause the background to be automatically cleared by the gpu
     * whenever the drawing ennironment is swapped, so we wont have to clear it
     * ourselves */
    setRGB0 (&context->drawing_environments[0],
             BACKGROUND_COLOR_RED,
             BACKGROUND_COLOR_GREEN,
             BACKGROUND_COLOR_BLUE);
    setRGB0 (&context->drawing_environments[1],
             BACKGROUND_COLOR_RED,
             BACKGROUND_COLOR_GREEN,
             BACKGROUND_COLOR_BLUE);

    /* and also set the flag to enable that to happen */
    context->drawing_environments[0].isbg = true;
    context->drawing_environments[1].isbg = true;

    /* initialize the state of the alternation between buffers */
    context->i_buffer = 0;
}

void display_context_switch (display_context_t *context) {

    /* initialize the gpu */
    ResetGraph (0); /* this completely resets the gpu */

    /* TODO: pal mode if necessary */

    /* set the display to display the image to the screen */
    SetDispMask (1);

    /* send the drawing and display environment configuration
     * to the gpu */
    PutDispEnv (&context->display_environments[context->i_buffer]);
    PutDrawEnv (&context->drawing_environments[context->i_buffer]);
}

void display_context_flip (display_context_t *context) {

    /* make sure all drawing operations are completed first */
    DrawSync (0);

    /* await vblank before switching */
    VSync (0);

    /* swap assigned buffer roles */
    context->i_buffer = (context->i_buffer + 1) % N_GRAPHICS_BUFFERS;

    /* send the now-swapped drawing and display environment configuration
     * to the gpu */
    PutDispEnv (&context->display_environments[context->i_buffer]);
    PutDrawEnv (&context->drawing_environments[context->i_buffer]);
}
