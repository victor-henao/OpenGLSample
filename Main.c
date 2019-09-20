#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Window.h"
#include "GLContext.h"
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"

int main(void)
{
    printf("Hi!\n");

    struct Window* window = window_create(800, 600, "Nani OpenGL");
    glcontext_create(window);

    shader_initialize("shaders/VS.glsl", "shaders/FS.glsl");

    struct Camera* camera = camera_create(75.0f, (float)window->width / (float)window->height);

    struct Mesh* cube = mesh_load("res/cube.obj");
    struct Mesh* cylinder = mesh_load("res/cylinder.obj");
    struct Mesh* cone = mesh_load("res/cone.obj");

    struct Texture* grass = texture_create("res/grass.jpg");
    struct Texture* wall = texture_create("res/wall.jpg");

    mesh_set_position(cube, -2, 0, 0);
    mesh_set_position(cone, 2, 0, 0);

    while (window_is_open(window))
    {
        static float t = 0.0f;

        window_update(window);
        window_clear(0.0f, 0.0f, 0.0f);

        camera_set_position(camera, sinf(t) * 5, 2, cosf(t) * 5);
        camera_look_at(camera, 0, 0, 0);

        texture_bind(grass);
        mesh_draw(cube);

        texture_bind(wall);
        mesh_draw(cylinder);
        mesh_draw(cone);

        window_swap_buffers(window);
        t += 0.005f;
    }

    texture_destroy(grass);
    texture_destroy(wall);

    mesh_destroy(cube);
    mesh_destroy(cylinder);
    mesh_destroy(cone);

    camera_destroy(camera);

    shader_destroy();

    glcontext_destroy(window);
    window_destroy(window);

    exit(0);
}