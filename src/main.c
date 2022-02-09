/* TODO: support PAL switch */
#define RESOLUTION_X 320
#define RESOLUTION_Y 240

#define CENTER_X (RESOLUTION_X / 2)
#define CENTER_Y (RESOLUTION_Y / 2)

#define UNIT (RESOLUTION_X / 2)

#define FOCAL_LENGTH 2

#define SCREEN_Z (FOCAL_LENGTH * UNIT)

typedef struct double_buffer_context_t {

    DRAWENV drawing_environments[2];
    DISPENV display_environments[2];

} double_buffer_context_t;

void main () {

    /* initialize the gpu */
    ResetGraph (0);

    
}
