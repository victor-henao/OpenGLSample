#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

struct Texture
{
    unsigned int id;
};

enum TextureError
{
    TEXTURE_MALLOC_FAILED = 1
};

struct Texture* texture_create(char* textureSource);
void texture_bind(struct Texture* texture);
void texture_destroy(struct Texture* texture);

#endif // !TEXTURE_H
