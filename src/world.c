#include <sys/types.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libapi.h>

#include "world.h"

/* the acceleration due to player controls */
#define PADDLE_ACCELERATION (ONE * 4)

/* the acceleration due to drag */
#define PADDLE_DRAG (ONE * 2)

/* the intensity of the collision force */
#define PADDLE_COLLISION_COEFFICIENT (ONE * 128)

/* the paddle height in pixels */
#define PADDLE_HEIGHT (ONE / 16)

/* the distance from the center of the paddle to one of its horizontal ends */
#define PADDLE_RADIUS (ONE / 8)

/* the inward distance from the edges of the screen to the limits of how far you can go */
#define WALL_PADDING (ONE / 16)

/* the x position of touching the left wall */
#define PADDLE_POSITION_X_MIN (PADDLE_RADIUS - ONE + WALL_PADDING)

/* the x position of touching the right wall */
#define PADDLE_POSITION_X_MAX (ONE - PADDLE_RADIUS - WALL_PADDING)

void world_init (world_t *world) {

    /* reset the position and momentum of the paddle */
    object_2d_init_3 (&world->paddle, 0, ONE / 2);

    /* reset the position and momentum of the ball */
    object_2d_init_3 (&world->ball, 0, 0);
}

void world_update (world_t *world, context_t *context) {

    /* reset the acceleration as we accumulate the forces activing on the
     * object before we integrate it */
    vec_2_init (&world->paddle.acceleration, 0, 0);

    /* dpad moves the paddles yeah */
    if (context->pad_buffers[0][0] == 0 && /* if controller is connected */
        (context->pad_buffers[0][1] >> 4) & 4) {  /* and if its type is correct */

        u_short state = *((u_short *) (&context->pad_buffers[0][2]));

        if ((state & (1 << 5)) == 0) /* right */
            world->paddle.acceleration.x += PADDLE_ACCELERATION;

        if ((state & (1 << 7)) == 0) /* left */
            world->paddle.acceleration.x -= PADDLE_ACCELERATION;
    }

    /* drag force */
    world->paddle.acceleration.x -= (world->paddle.velocity.x * PADDLE_DRAG) >> 12;

    /* wall collision force */
    if (world->paddle.position.x < PADDLE_POSITION_X_MIN)
        world->paddle.acceleration.x += (PADDLE_COLLISION_COEFFICIENT *
                                         (PADDLE_POSITION_X_MIN -
                                          world->paddle.position.x)) >> 12;
    if (world->paddle.position.x > PADDLE_POSITION_X_MAX)
        world->paddle.acceleration.x += (PADDLE_COLLISION_COEFFICIENT *
                                         (PADDLE_POSITION_X_MAX -
                                          world->paddle.position.x)) >> 12;

    /* integrate the motion of the paddle and the ball */
    object_2d_integrate (&world->paddle);
    object_2d_integrate (&world->ball);

    ///* the dpad will move the player around */
    ///* TODO something better and more interesting,
    // * but this'll do for early demo hehe */
    ///* TODO we gotta have some predefined values for checking for certain buttons ! */

    //if (context->pad_buffers[0][0] == 0 && /* if controller is connected */
    //    (context->pad_buffers[0][1] >> 4) & 4) {  /* and if its type is correct */

    //    int increment = ONE / FRAMES_PER_SECOND / 8;

    //    u_short state = *((u_short *) (&context->pad_buffers[0][2]));
    //    if ((state & (1 << 4)) == 0) /* up */
    //        world->y -= increment;
    //    if ((state & (1 << 5)) == 0) /* right */
    //        world->x += increment;
    //    if ((state & (1 << 6)) == 0) /* down */
    //        world->y += increment;
    //    if ((state & (1 << 7)) == 0) /* left */
    //        world->x -= increment;
    //}
}

void world_draw (world_t *world, context_t *context) {

    /* allocate a tile primitive to draw the paddle */
    TILE *primitive_paddle
        = (TILE *) context_allocate_primitive (context, sizeof (TILE));

    /* set the primitive type */
    setTile (primitive_paddle);

    /* set the color of the paddle */
    setRGB0 (primitive_paddle, 255, 255, 255);

    /* set the size of the paddle */
    setWH (primitive_paddle, (PADDLE_RADIUS * 2) >> 12, PADDLE_HEIGHT >> 12);

    /* set the position of the tile to match that of the paddle */
    setXY0 (primitive_paddle, ((world->paddle.position.x * UNIT) >> 12)  + CENTER_X - PADDLE_RADIUS,
                              ((world->paddle.position.y * UNIT) >> 12)  + CENTER_Y);

    /* add the primitive to the ordering table */
    addPrim (context->graphics.ordering_table + 0, primitive_paddle);

//    /* we will draw a spinning pyramid as the player hehe */
//    /* TODO something more interesting, this will do for now !! */
//
//    /* setup the vertices */
//    SVECTOR vertices[5] = {
//        {0,       -ONE / 3,  0},
//        {-ONE / 3, ONE / 3,  ONE / 3},
//        { ONE / 3, ONE / 3,  ONE / 3},
//        { ONE / 3, ONE / 3, -ONE / 3},
//        {-ONE / 3, ONE / 3, -ONE / 3},
//    };
//
//    /* setup the triangle faces */
//    size_t faces[N_FACES][3] = {
//        {0, 1, 2},
//        {0, 2, 3},
//        {0, 3, 4},
//        {0, 4, 1},
//        {1, 2, 3},
//        {1, 3, 4},
//    };
//
//    /* setup the triangle face colors */
//    CVECTOR face_colors[N_FACES] = {
//        {0, 255, 127},
//        {0, 0,   127},
//        {0, 255, 127},
//        {0, 0,   127},
//        {0, 255, 127},
//        {0, 0,   127},
//    };
//
//    /* setup the transformation matrix */
//    MATRIX matrix;
//    short angle = VSync (-1) * ONE / FRAMES_PER_SECOND / 4;
//    SVECTOR vector_rotation    = {0, angle, 0};
//    VECTOR  vector_scale       = {UNIT, UNIT, UNIT};
//    VECTOR  vector_translation = {world->x, 0, SCREEN_Z - world->y};
//    RotMatrix   (&vector_rotation, &matrix);
//    TransMatrix (&matrix, &vector_translation);
//    ScaleMatrix (&matrix, &vector_scale);
//    SetRotMatrix   (&matrix);
//    SetTransMatrix (&matrix);
//
//    /* draw each face */
//    for (size_t i = 0; i < N_FACES; i++) {
//
//        /* this will be used for z sorting */
//        int z_index = 0;
//
//        /* depth cue and flags output by gte functions */
//        long depth_cue, flags;
//
//        /* allocate a 3 vertex polygon primitive to draw the face with */
//        POLY_F3 *primitive
//            = (POLY_F3 *) context_allocate_primitive (context, sizeof (POLY_F3));
//
//        /* set the primitive type */
//        setPolyF3 (primitive);
//
//        /* set the color */
//        setRGB0 (primitive,
//                 face_colors[i].r,
//                 face_colors[i].g,
//                 face_colors[i].b);
//
//        /* transform each vertex and output to the primitive screen coordinates
//         * and we will sum and average the rough z values for sorting */
//        z_index += RotTransPers (&vertices[faces[i][0]],
//                                 (long *) &primitive->x0,
//                                 &depth_cue,
//                                 &flags);
//        z_index += RotTransPers (&vertices[faces[i][1]],
//                                 (long *) &primitive->x1,
//                                 &depth_cue,
//                                 &flags);
//        z_index += RotTransPers (&vertices[faces[i][2]],
//                                 (long *) &primitive->x2,
//                                 &depth_cue,
//                                 &flags);
//        z_index /= 3;
//
//        /* add the primitive to the ordering table sorted z index
//         * but only if its in bounds !! */
//        if (z_index > 0 && z_index < ORDERING_TABLE_LENGTH)
//            addPrim (context->graphics.ordering_table + z_index, primitive);
//    }
}
