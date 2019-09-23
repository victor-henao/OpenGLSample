#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>

struct Window
{
    HINSTANCE       hInstance;
    unsigned int    width;
    unsigned int    height;
    char*           title;
    BOOL            isOpen;
    HWND            handle;
    WNDCLASSEX      windowClass;
    MSG             message;
    HDC             deviceContext;
    HGLRC           renderingContext;
    float           frameTime;
};

enum WindowError
{
    WINDOW_MALLOC_FAILED = 1,
    WINDOW_REGISTER_CLASS_FAILED
};

struct Window* window_create(unsigned int width, unsigned int height, char* title);
BOOL window_is_open(struct Window* window);
LRESULT CALLBACK window_procedure(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam);
void window_update(struct Window* window);
void window_clear(float red, float green, float blue);
void window_swap_buffers(struct Window* window);
float window_get_frame_time(struct Window* window);
void window_destroy(struct Window* window);

#endif // !WINDOW_H
