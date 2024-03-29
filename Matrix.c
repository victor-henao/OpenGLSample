#include "Matrix.h"

void matrix_identity(float matrix[4][4])
{
    for (unsigned int i = 0; i < 4; i++)
        for (unsigned int j = 0; j < 4; j++)
            if (i == j)
                matrix[i][j] = 1;
            else
                matrix[i][j] = 0;
}

void matrix_copy(float source[4][4], float destination[4][4])
{
    for (unsigned int i = 0; i < 4; i++)
        for (unsigned int j = 0; j < 4; j++)
            destination[i][j] = source[i][j];
}

void matrix_scale(float matrix[4][4], float vector[3])
{
    for (unsigned int i = 0; i < 3; i++)
        matrix[i][i] = vector[i];
}

void matrix_translate(float matrix[4][4], float vector[3])
{
    for (unsigned int i = 0; i < 3; i++)
        matrix[3][i] = vector[i];
}

void matrix_rotate(float matrix[4][4], float angle, char axis)
{
    angle = angle * (float)M_PI / 180.0f;

    switch (axis)
    {
    case 'x':
    {
        matrix[1][1] =  cosf(angle);
        matrix[1][2] =  sinf(angle);
        matrix[2][1] = -sinf(angle);
        matrix[2][2] =  cosf(angle);
    }
    break;
    case 'y':
    {
        matrix[0][0] =  cosf(angle);
        matrix[0][2] = -sinf(angle);
        matrix[2][0] =  sinf(angle);
        matrix[2][2] =  cosf(angle);
    }
    break;
    case 'z':
    {
        matrix[0][0] =  cosf(angle);
        matrix[0][1] =  sinf(angle);
        matrix[1][0] = -sinf(angle);
        matrix[1][1] =  cosf(angle);
    }
    break;
    default:
        break;
    }
}