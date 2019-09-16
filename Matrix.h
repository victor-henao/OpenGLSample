#ifndef TRANSFORM_H
#define MATRIX_H

#define _USE_MATH_DEFINES
#include <math.h>

void matrix_identity(float matrix[4][4]);
void matrix_copy(float source[4][4], float destination[4][4]);
void matrix_scale(float matrix[4][4], float vector[3]);
void matrix_translate(float matrix[4][4], float vector[3]);
void matrix_rotate(float matrix[4][4], float angle, char axis);

#endif // !MATRIX_H
