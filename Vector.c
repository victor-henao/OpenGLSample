#include "Vector.h"

void vector_cross(float vector1[3], float vector2[3], float result[3])
{
    result[0] =   (vector1[1] * vector2[2]) - (vector1[2] * vector2[1]);
    result[1] = -((vector1[2] * vector2[0]) - (vector1[0] * vector2[2]));
    result[2] =   (vector1[0] * vector2[1]) - (vector1[1] * vector2[0]);
}

void vector_sub(float vector1[3], float vector2[3], float result[3])
{
    for (unsigned int i = 0; i < 3; i++)
        result[i] = vector1[i] - vector2[i];
}

void vector_normalize(float vector[3])
{
    float length = sqrtf(
        powf(vector[0], (float)2) +
        powf(vector[1], (float)2) +
        powf(vector[2], (float)2)
    );

    for (unsigned int i = 0; i < 3; i++)
        vector[i] = vector[i] / length;
}

void vector_negate(float vector[3])
{
    for (unsigned int i = 0; i < 3; i++)
        vector[i] = -vector[i];
}

float vector_dot(float vector1[3], float vector2[3])
{
    return (vector1[0] * vector2[0]) + (vector1[1] * vector2[1]) + (vector1[2] * vector2[2]);
}