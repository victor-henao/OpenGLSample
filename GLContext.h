#ifndef GLCONTEXT_H
#define GLCONTEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "Window.h"

enum GLContextError
{
    GLCONTEXT_SET_PIXEL_FORMAT_FAILED = 1,
    GLCONTEXT_INITIALIZE_GLEW_FAILED
};

void glcontext_create(struct Window* window);
void glcontext_destroy(struct Window* window);

#endif // !GLCONTEXT_H
