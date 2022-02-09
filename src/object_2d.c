#include <sys/types.h>
#include <libgte.h>

#include "config.h"
#include "object_2d.h"

void object_2d_init (object_2d_t *object,
                     vec_2_t position,
                     vec_2_t velocity,
                     vec_2_t acceleration) {

    object->position     = position;
    object->velocity     = velocity;
    object->acceleration = acceleration;
}

void object_2d_init_2 (object_2d_t *object,
                       int position_x,
                       int position_y,
                       int velocity_x,
                       int velocity_y,
                       int acceleration_x,
                       int acceleration_y) {

    vec_2_t position     = vec_2_make (position_x,     position_y);
    vec_2_t velocity     = vec_2_make (velocity_x,     velocity_y);
    vec_2_t acceleration = vec_2_make (acceleration_x, acceleration_y);
    object_2d_init (object, position, velocity, acceleration);
}

void object_2d_init_3 (object_2d_t *object, int position_x, int position_y) {

    object_2d_init_2 (object, position_x, position_y, 0, 0, 0, 0);
}

void object_2d_integrate (object_2d_t *object) {

    object->velocity = vec_2_add (object->velocity,
                                  vec_2_multiply_scalar (object->acceleration,
                                                         TIME_STEP));
    object->position = vec_2_add (object->position,
                                  vec_2_multiply_scalar (object->velocity,
                                                         TIME_STEP));
}
