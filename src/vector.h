#ifndef VECTOR_2D_H
#define VECTOR_2D_H

/* represents a 2d vector in fixed point */
typedef struct vec_2_t {

    /* fixed point coordinates */
    int x, y;

} vec_2_t;

/* initialize a vector with coordinates */
void vec_2_init (vec_2_t *vector, int x, int y);

/* construct a vector */
vec_2_t vec_2_make (int x, int y);

/* add two fixed point vectors */
vec_2_t vec_2_add (vec_2_t a, vec_2_t b);

/* multiply a fixed point vector by a fixed point scalar */
vec_2_t vec_2_multiply_scalar (vec_2_t vector, int scalar);

#endif /* VECTOR_2D_H */
