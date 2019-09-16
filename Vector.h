#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

void vector_cross(float vector1[3], float vector2[3], float result[3]);
void vector_sub(float vector1[3], float vector2[3], float result[3]);
void vector_normalize(float vector[3]);
void vector_negate(float vector[3]);
float vector_dot(float vector1[3], float vector2[3]);

#endif // !VECTOR_H
