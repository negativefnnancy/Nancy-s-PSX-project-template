#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libapi.h>

#include "world.h"

void world_init (world_t *world) {

    /* reset the position of the player */
    world->x = 0;
    world->y = 0;
}

void world_update (world_t *world, context_t *context) {

    /* the dpad will move the player around */
    /* TODO something better and more interesting,
     * but this'll do for early demo hehe */
    /* TODO we gotta have some predefined values for checking for certain buttons ! */

    if (context->pad_buffers[0][0] == 0 && /* if controller is connected */
        (context->pad_buffers[0][1] >> 4) & 4) {  /* and if its type is correct */

        int increment = ONE / FRAMES_PER_SECOND / 8;

        u_short state = *((u_short *) (&context->pad_buffers[0][2]));
        if ((state & (1 << 4)) == 0) /* up */
            world->y -= increment;
        if ((state & (1 << 5)) == 0) /* right */
            world->x += increment;
        if ((state & (1 << 6)) == 0) /* down */
            world->y += increment;
        if ((state & (1 << 7)) == 0) /* left */
            world->x -= increment;
    }
}

#define N_FACES 6
void world_draw (world_t *world, context_t *context) {

    /* we will draw a spinning pyramid as the player hehe */
    /* TODO something more interesting, this will do for now !! */

    /* setup the vertices */
    SVECTOR vertices[5] = {
        {0,       -ONE / 3,  0},
        {-ONE / 3, ONE / 3,  ONE / 3},
        { ONE / 3, ONE / 3,  ONE / 3},
        { ONE / 3, ONE / 3, -ONE / 3},
        {-ONE / 3, ONE / 3, -ONE / 3},
    };

    /* setup the triangle faces */
    size_t faces[N_FACES][3] = {
        {0, 1, 2},
        {0, 2, 3},
        {0, 3, 4},
        {0, 4, 1},
        {1, 2, 3},
        {1, 3, 4},
    };

    /* setup the triangle face colors */
    CVECTOR face_colors[N_FACES] = {
        {0, 255, 127},
        {0, 0,   127},
        {0, 255, 127},
        {0, 0,   127},
        {0, 255, 127},
        {0, 0,   127},
    };

    /* setup the transformation matrix */
    MATRIX matrix;
    short angle = VSync (-1) * ONE / FRAMES_PER_SECOND / 4;
    SVECTOR vector_rotation    = {0, angle, 0};
    VECTOR  vector_scale       = {UNIT, UNIT, UNIT};
    VECTOR  vector_translation = {world->x, 0, SCREEN_Z - world->y};
    RotMatrix   (&vector_rotation, &matrix);
    TransMatrix (&matrix, &vector_translation);
    ScaleMatrix (&matrix, &vector_scale);
    SetRotMatrix   (&matrix);
    SetTransMatrix (&matrix);

    /* draw each face */
    for (size_t i = 0; i < N_FACES; i++) {

        /* this will be used for z sorting */
        int z_index = 0;

        /* depth cue and flags output by gte functions */
        long depth_cue, flags;

        /* allocate a 3 vertex polygon primitive to draw the face with */
        POLY_F3 *primitive
            = (POLY_F3 *) context_allocate_primitive (context, sizeof (POLY_F3));

        /* set the primitive type */
        setPolyF3 (primitive);

        /* set the color */
        setRGB0 (primitive,
                 face_colors[i].r,
                 face_colors[i].g,
                 face_colors[i].b);

        /* transform each vertex and output to the primitive screen coordinates
         * and we will sum and average the rough z values for sorting */
        z_index += RotTransPers (&vertices[faces[i][0]],
                                 (long *) &primitive->x0,
                                 &depth_cue,
                                 &flags);
        z_index += RotTransPers (&vertices[faces[i][1]],
                                 (long *) &primitive->x1,
                                 &depth_cue,
                                 &flags);
        z_index += RotTransPers (&vertices[faces[i][2]],
                                 (long *) &primitive->x2,
                                 &depth_cue,
                                 &flags);
        z_index /= 3;

        /* add the primitive to the ordering table sorted z index
         * but only if its in bounds !! */
        if (z_index > 0 && z_index < ORDERING_TABLE_LENGTH)
            addPrim (context->graphics.ordering_table + z_index, primitive);
    }
}
