#ifndef LIGHT_H
#define LIGHT_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "Shader.h"
#include "Vector.h"

struct Light
{
    unsigned int vertexArray;
    unsigned int vertexBuffer;
    struct Vector3f position;
    struct Vector3f color;
};

enum LightError
{
    LIGHT_MALLOC_FAILED = 1
};

struct Light* light_create(float red, float green, float blue);
void light_set_position(struct Light* light, float x, float y, float z);
void light_set_color(struct Light* light, float red, float green, float blue);
void light_illuminate(struct Light* light, struct Shader* shader);
void light_destroy(struct Light* light);

#endif // !LIGHT_H
