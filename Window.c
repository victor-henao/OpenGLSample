#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Window.h"

unsigned int timerStart = 0;

struct Window* window_create(unsigned int width, unsigned int height, char* title)
{
    struct Window* window = malloc(sizeof(struct Window));

    if (window == NULL)
    {
        MessageBox(NULL, "Couldn't allocate memory for the window!", "Error", MB_OK);
        exit(WINDOW_MALLOC_FAILED);
    }

    window->hInstance   = GetModuleHandle(NULL);
    window->width       = width;
    window->height      = height;
    window->title       = title;

    ZeroMemory(&window->windowClass, sizeof(WNDCLASSEX));

    char* className = "window class";

    window->windowClass.cbSize          = sizeof(WNDCLASSEX);
    window->windowClass.style           = 0;
    window->windowClass.lpfnWndProc     = window_procedure;
    window->windowClass.hInstance       = window->hInstance;
    window->windowClass.hCursor         = LoadCursor(NULL, IDC_ARROW);
    window->windowClass.lpszClassName   = className;

    if (!RegisterClassEx(&window->windowClass))
    {
        MessageBox(NULL, "Couldn't register window class!", "Error", MB_OK);
        exit(WINDOW_REGISTER_CLASS_FAILED);
    }

    RECT windowRectangle = { 0, 0, window->width, window->height };
    AdjustWindowRect(&windowRectangle, WS_OVERLAPPED, FALSE);

    GetWindowRect(window->handle, &windowRectangle);

    unsigned int x = (GetSystemMetrics(SM_CXSCREEN) - windowRectangle.right) / 2;
    unsigned int y = (GetSystemMetrics(SM_CYSCREEN) - windowRectangle.bottom) / 2;

    window->handle = CreateWindowEx(
        0,
        window->windowClass.lpszClassName,
        window->title,
        WS_OVERLAPPEDWINDOW,
        x, y, // Window position
        windowRectangle.right - windowRectangle.left, // Window width
        windowRectangle.bottom - windowRectangle.top, // Window height
        NULL,
        NULL,
        window->hInstance,
        NULL
    );

    ShowWindow(window->handle, SW_SHOW);

    window->isOpen = TRUE;

    timerStart = glutGet(GLUT_ELAPSED_TIME);

    return window;
}

BOOL window_is_open(struct Window* window)
{
    return window->isOpen;
}

LRESULT CALLBACK window_procedure(HWND hWnd, unsigned int message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SIZE:
        glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
        break;
    //case WM_KEYDOWN:
    //{

    //}
    case WM_CLOSE:
    {
        PostMessage(hWnd, WM_CLOSE, 0, 0);
        return 0;
    }
     break;
    default:
        break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

void window_update(struct Window* window)
{
    if (PeekMessage(&window->message, NULL, 0, 0, PM_REMOVE))
    {
        TranslateMessage(&window->message);
        DispatchMessage(&window->message);

        if (window->message.message == WM_CLOSE)
            window->isOpen = FALSE;
    }
}

void window_clear(float red, float green, float blue)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(red, green, blue, 1.0f);
}

void window_swap_buffers(struct Window* window)
{
    static unsigned int fps = 0;

    fps++;
    unsigned int diff = glutGet(GLUT_ELAPSED_TIME) - timerStart;
    window->frameTime = (float)diff / (float)fps;

    if (diff >= 1000)
    {
        printf("FPS = %u\n", fps);
        timerStart = glutGet(GLUT_ELAPSED_TIME);
        fps = 0;
    }

    SwapBuffers(window->deviceContext);
}

float window_get_frame_time(struct Window* window)
{
    return window->frameTime;
}

void window_destroy(struct Window* window)
{
    UnregisterClass(window->windowClass.lpszClassName, window->hInstance);

    free(window);
}