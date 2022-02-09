#ifndef CONFIG_H
#define CONFIG_H

/* screen resolution */
/* TODO: support PAL switch */
/* TODO: interlace mode switch */
#define RESOLUTION_X 320
#define RESOLUTION_Y 240

/* the center of the screen */
#define CENTER_X (RESOLUTION_X / 2)
#define CENTER_Y (RESOLUTION_Y / 2)

/* the unit length we will use for normalized device coordinates
 * which we will set to be half the width of the screen */
#define UNIT (RESOLUTION_X / 2)

/* focal length in normalized device units
 * this is the distance from the eye to the screen */
#define FOCAL_LENGTH 2

/* this is the distance from the eye to the screen in pixels
 * and this is used in GTE perspective projection calculations */
#define SCREEN_Z (FOCAL_LENGTH * UNIT)

/* intended frames per second
 * we will use this for timing calculations */
/* TODO: support PAL switch */
#define FRAMES_PER_SECOND 60

/* offset in vram of the first buffer in the double buffering setup */
#define VRAM_BUFFER_1_X 0
#define VRAM_BUFFER_1_Y 0

/* and that of the second buffer */
#define VRAM_BUFFER_2_X 0
#define VRAM_BUFFER_2_Y RESOLUTION_Y

/* the background clear color */
#define BACKGROUND_COLOR_RED   127
#define BACKGROUND_COLOR_GREEN 127
#define BACKGROUND_COLOR_BLUE  127

/* the number of buffers to swap between (e.g. 2 for double buffering) */
#define N_GRAPHICS_BUFFERS 2

/* the number of ordering tables to swap between */
#define N_ORDERING_TABLES 2

/* the number of primitive buffers to swap between */
#define N_PRIMITIVE_BUFFERS 2

/* the number of entries in an ordering table */
#define ORDERING_TABLE_LENGTH 2048

/* the size of primitive buffers */
#define PRIMITIVE_BUFFER_SIZE 32768

/* the size of the buffers used to store the state of gamepad */
#define PAD_BUFFER_SIZE 34

/* the number of gamepad state pad buffers */
#define N_PAD_BUFFERS 2

#endif /* CONFIG_H */
