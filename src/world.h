#ifndef WORLD_H
#define WORLD_H

#include "context.h"
#include "object_2d.h"

/* represents the state of the game world */
typedef struct world_t {

    /* object to represent the paddle */
    object_2d_t paddle;

    /* object to represent the ball */
    object_2d_t ball;

} world_t;

/* initialize the state of the world for the first frame */
void world_init (world_t *world);

/* update the state of the world to the next frame */
void world_update (world_t *world, context_t *context);

/* prepare the stream of primitive packets to render the frame based on the
 * current state of the world */
void world_draw (world_t *world, context_t *context);

#endif /* WORLD_H */
