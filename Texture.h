#ifndef TEXTURE_H
#define TEXTURE_H

struct Texture
{
    unsigned int handle;
};

enum TextureError
{
    TEXTURE_MALLOC_FAILED = 1
};

struct Texture* texture_create(char* texturePath);
void texture_bind(struct Texture* texture);
void texture_destroy(struct Texture* texture);

#endif // !TEXTURE_H
