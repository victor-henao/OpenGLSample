#ifndef TRANSFORM_H
#define TRANSFORM_H

#define _USE_MATH_DEFINES
#include <math.h>

void transform_identity(float matrix[4][4]);
void transform_copy(float source[4][4], float destination[4][4]);
void transform_multiply(float matrix1[4][4], float matrix2[4][4], float result[4][4]);
void transform_scale(float matrix[4][4], float vector[3]);
void transform_translate(float matrix[4][4], float vector[3]);
void transform_rotate(float matrix[4][4], float angle, char axis);

#endif // !TRANSFORM_H
