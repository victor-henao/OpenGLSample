#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "Texture.h"
#include "SFML/Graphics.h"

struct Texture* texture_create(char* texturePath)
{
    struct Texture* texture = malloc(sizeof(struct Texture));

    if (texture == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for the texture!");
        exit(TEXTURE_MALLOC_FAILED);
    }

    glGenTextures(1, &texture->handle);
    glBindTexture(GL_TEXTURE_2D, texture->handle);

    sfImage* image = sfImage_createFromFile(texturePath);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sfImage_getSize(image).x, sfImage_getSize(image).y, 0, GL_RGBA, GL_UNSIGNED_BYTE, sfImage_getPixelsPtr(image));
    glGenerateMipmap(GL_TEXTURE_2D);

    sfImage_destroy(image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

void texture_bind(struct Texture* texture)
{
    glBindTexture(GL_TEXTURE_2D, texture->handle);
}

void texture_destroy(struct Texture* texture)
{
    glDeleteTextures(1, &texture->handle);

    free(texture);
}