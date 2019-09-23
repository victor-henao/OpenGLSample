#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "Context.h"

void context_create(struct Window* window)
{
    window->deviceContext = GetDC(window->handle);

    int pixelFormat;
    PIXELFORMATDESCRIPTOR pixelFormatDescriptor;

    pixelFormatDescriptor.nSize         = sizeof(PIXELFORMATDESCRIPTOR);
    pixelFormatDescriptor.nVersion      = 1;
    pixelFormatDescriptor.iLayerType    = PFD_MAIN_PLANE;
    pixelFormatDescriptor.dwFlags       = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    pixelFormatDescriptor.cDepthBits    = 32;
    pixelFormatDescriptor.cColorBits    = 24;
    pixelFormatDescriptor.iPixelType    = PFD_TYPE_RGBA;

    pixelFormat = ChoosePixelFormat(window->deviceContext, &pixelFormatDescriptor);

    if (!SetPixelFormat(window->deviceContext, pixelFormat, &pixelFormatDescriptor))
    {
        MessageBox(NULL, "Couldn't set pixel format!", "Error", MB_OK);
        exit(GLCONTEXT_SET_PIXEL_FORMAT_FAILED);
    }

    window->renderingContext = wglCreateContext(window->deviceContext);
    wglMakeCurrent(window->deviceContext, window->renderingContext);

    if (glewInit() != GLEW_OK)
    {
        MessageBox(NULL, "Couldn't initialize GLEW!", "Error", MB_OK);
        exit(GLCONTEXT_INITIALIZE_GLEW_FAILED);
    }

    glEnable(GL_DEPTH_TEST);

    printf("Using GLEW version %s\n", glewGetString(GLEW_VERSION));
    printf("Using OpenGL version %s\n", glGetString(GL_VERSION));
}

void context_destroy(struct Window* window)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(window->renderingContext);
    ReleaseDC(window->handle, window->deviceContext);
}