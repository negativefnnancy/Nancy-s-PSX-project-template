#ifndef OBJECT_2D_H
#define OBJECT_2D_H

#include "vector.h"

/* represents a 2d physical object with momentum! */
typedef struct object_2d_t {

    vec_2_t position;
    vec_2_t velocity;
    vec_2_t acceleration;

} object_2d_t;

/* initialize a 2d object with vectors */
void object_2d_init (object_2d_t *object,
                     vec_2_t position,
                     vec_2_t velocity,
                     vec_2_t acceleration);

/* initialize a 2d object with direct fixed point values */
void object_2d_init_2 (object_2d_t *object,
                       int position_x,
                       int position_y,
                       int velocity_x,
                       int velocity_y,
                       int acceleration_x,
                       int acceleration_y);

/* initialize a 2d object with position only */
void object_2d_init_3 (object_2d_t *object, int position_x, int position_y);

/* update the state of the object by integrating the velocity and position
 * if acceleration isnt meant to be constant, it should be updated
 * before each time this is called ! */
/* TODO have alternate functions that integrate variable timesteps */
void object_2d_integrate (object_2d_t *object);

#endif /* OBJECT_2D_H */
