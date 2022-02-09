#include "world.h"

void world_init (world_t *world) {

    /* reset the position of the player */
    world->x = 0;
    world->y = 0;
}

void world_update (world_t *world, context_t *context) {

    /* TODO stuff about a character position that u can contrel with d pad hehe */
}

void world_draw (world_t *world, context_t *context) {

    /* allocate a 4 vertex polygon to represent the player XD */
    POLY_F4 *primitive
        = (POLY_F4 *) context_allocate_primitive (context, sizeof (POLY_F4));

    /* set the primitive type */
    setPolyF4 (primitive);

    /* set the color to white */
    setRGB0 (primitive, 255, 255, 255);

    /* set the position */
    setXY4 (primitive, world->x - 10, world->y - 10,
                       world->x + 10, world->y - 10,
                       world->x + 10, world->y + 10,
                       world->x - 10, world->y + 10);

    /* add the primitive to the ordering table at index 0*/
    addPrim (context->graphics.ordering_table + 0, primitive);
}
