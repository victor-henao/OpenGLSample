#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

struct Texture* texture_create(char* textureSource)
{
    struct Texture* texture = malloc(sizeof(struct Texture));

    if (texture == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for the texture!");
        exit(TEXTURE_MALLOC_FAILED);
    }

    glGenTextures(1, &texture->id);

    unsigned int width, height, channelCount;

    glBindTexture(GL_TEXTURE_2D, texture->id);
    unsigned char* image = stbi_load(textureSource, &width, &height, &channelCount, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(image);

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