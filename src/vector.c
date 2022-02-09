#include "vector.h"

void vec_2_init (vec_2_t *vector, int x, int y) {

    vector->x = x;
    vector->y = y;
}

vec_2_t vec_2_make (int x, int y) {

    vec_2_t vector;
    vec_2_init (&vector, x, y);
    return vector;
}

vec_2_t vec_2_add (vec_2_t a, vec_2_t b) {

    return vec_2_make (a.x + b.x, a.y + b.y);
}

vec_2_t vec_2_multiply_scalar (vec_2_t vector, int scalar) {

    return vec_2_make  (vector.x * scalar >> 12, vector.y * scalar >> 12);
}
