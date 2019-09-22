#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Window.h"
#include "GLContext.h"
#include "Shader.h"
#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"
#include "Light.h"

int main(void)
{
    printf("Hi!\n");

    struct Window* window = window_create(800, 600, "Nani OpenGL");
    glcontext_create(window);

    struct Shader* shader = shader_create("shaders/VS.glsl", "shaders/FS.glsl");
    struct Camera* camera = camera_create(75.0f, (float)window->width / (float)window->height);
    struct Mesh* cube = mesh_load("res/cube.obj");
    struct Mesh* cylinder = mesh_load("res/cylinder.obj");
    struct Mesh* cone = mesh_load("res/cone.obj");
    struct Texture* grass = texture_create("res/grass.jpg");
    struct Texture* wall = texture_create("res/wall.jpg");
    struct Light* light = light_create(1.0f, 0.0f, 0.0f);

    camera_set_position(camera, 2, 2, 3);
    mesh_set_position(cube, -2, 0, 0);
    mesh_set_position(cone, 2, 0, 0);

    while (window_is_open(window))
    {
        static float t = 0.0f;

        window_update(window);
        window_clear(0.0f, 0.0f, 0.0f);

        light_illuminate(light, shader);
        light_set_position(light, cosf(t) * 5, 0.0f, sinf(t) * 5);

        camera_look_at(camera, shader, 0, 0, 0);

        texture_bind(grass);
        mesh_draw(cube, shader);

        texture_bind(wall);
        mesh_draw(cylinder, shader);
        mesh_draw(cone, shader);

        window_swap_buffers(window);
        t += 0.005f;
    }

    light_destroy(light);
    texture_destroy(grass);
    texture_destroy(wall);
    mesh_destroy(cube);
    mesh_destroy(cylinder);
    mesh_destroy(cone);
    camera_destroy(camera);
    shader_destroy(shader);

    glcontext_destroy(window);
    window_destroy(window);

    exit(0);
}