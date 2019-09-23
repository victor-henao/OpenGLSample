#include "Texture.h"
#include "SFML/Graphics.h"

struct Texture* texture_create(char* textureSource)
{
    struct Texture* texture = malloc(sizeof(struct Texture));

    if (texture == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for the texture!");
        exit(TEXTURE_MALLOC_FAILED);
    }

    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    sfImage* image = sfImage_createFromFile(textureSource);

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
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

void texture_destroy(struct Texture* texture)
{
    glDeleteTextures(1, &texture->id);

    free(texture);
}