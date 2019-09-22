#include "Light.h"
#include "Shader.h"

struct Light* light_create(float red, float green, float blue)
{
    struct Light* light = malloc(sizeof(struct Light));

    if (light == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for the light!");
        exit(LIGHT_MALLOC_FAILED);
    }

    light->position = (struct Vector3f){ 0.0f, 0.0f, 0.0f };
    light->color    = (struct Vector3f){ red, green, blue };

    glGenVertexArrays(1, &light->vertexArray);
    glBindVertexArray(light->vertexArray);

    glGenBuffers(1, &light->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, light->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(struct Vector3f), (float[3]) { light->position.x, light->position.y, light->position.z }, GL_STATIC_DRAW);

    return light;
}

void light_set_position(struct Light* light, float x, float y, float z)
{
    light->position.x = x;
    light->position.y = y;
    light->position.z = z;
}

void light_set_color(struct Light* light, float red, float green, float blue)
{
    light->color.x = red;
    light->color.y = green;
    light->color.z = blue;
}

void light_illuminate(struct Light* light, struct Shader* shader)
{
    glUseProgram(shader->program);

    float position[3]   = { light->position.x, light->position.y, light->position.z };
    float color[3]      = { light->color.x, light->color.y, light->color.z };

    unsigned int positionLocation = glGetUniformLocation(shader->program, "lightPosition");
    glUniform3fv(positionLocation, 1, (float*)position);

    unsigned int colorLocation = glGetUniformLocation(shader->program, "lightColor");
    glUniform3fv(colorLocation, 1, (float*)color);

    glBindVertexArray(light->vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, light->vertexBuffer);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}

void light_destroy(struct Light* light)
{
    free(light);
}