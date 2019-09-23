#ifndef CONTEXT_H
#define CONTEXT_H

#include "Window.h"

enum GLContextError
{
    GLCONTEXT_SET_PIXEL_FORMAT_FAILED = 1,
    GLCONTEXT_INITIALIZE_GLEW_FAILED
};

void context_create(struct Window* window);
void context_destroy(struct Window* window);

#endif // !CONTEXT_H
