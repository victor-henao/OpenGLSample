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

    float cubeVertices[] =
    {    // Position         // Color          // Texture
        -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

        -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f, 0.4f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

        -1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

        -1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
         1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
         1.0f, 1.0f,  1.0f, 0.0f, 0.4f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

        -1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f,  1.0f, 0.0f, 0.4f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

        1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f,  1.0f,  1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -1.0f,  1.0f, 0.0f, 0.4f, 1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
    };

    float groundVertices[] =
    {
        -1.0f, 0.0f, -1.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f,
         1.0f, 0.0f, -1.0f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,
         1.0f, 0.0f,  1.0f, 0.0f, 0.5f, 0.0f, 1.0f, 1.0f,
        -1.0f, 0.0f,  1.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f
    };

    float wallVertices[] =
    {
        -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
         1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    
    unsigned int squareElements[] =
    {
        0, 1, 2,
        2, 3, 0
    };

    unsigned int cubeElements[] =
    {
        0, 1, 2,
        2, 3, 0,

        4, 5, 6,
        6, 7, 4,

        8,  9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    struct Window* window = window_create(800, 600, "Nani OpenGL");
    glcontext_create(window);

    shader_initialize("shaders/VS.glsl", "shaders/FS.glsl");

    struct Camera* camera = camera_create(75.0f, (float)window->width / (float)window->height);

    struct Mesh* cube1 = mesh_create(cubeVertices, sizeof(cubeVertices), cubeElements, sizeof(cubeElements));
    struct Mesh* cube2 = mesh_create(cubeVertices, sizeof(cubeVertices), cubeElements, sizeof(cubeElements));
    struct Mesh* cube3 = mesh_create(cubeVertices, sizeof(cubeVertices), cubeElements, sizeof(cubeElements));
    struct Mesh* cube4 = mesh_create(cubeVertices, sizeof(cubeVertices), cubeElements, sizeof(cubeElements));
    struct Mesh* ground = mesh_create(groundVertices, sizeof(groundVertices), squareElements, sizeof(squareElements));
    struct Mesh* wall1 = mesh_create(wallVertices, sizeof(wallVertices), squareElements, sizeof(squareElements));
    struct Mesh* wall2 = mesh_create(wallVertices, sizeof(wallVertices), squareElements, sizeof(squareElements));
    struct Mesh* wall3 = mesh_create(wallVertices, sizeof(wallVertices), squareElements, sizeof(squareElements));
    struct Mesh* wall4 = mesh_create(wallVertices, sizeof(wallVertices), squareElements, sizeof(squareElements));

    struct Texture* crate = texture_create("res/crate.jpg");
    struct Texture* grass = texture_create("res/grass.jpg");
    struct Texture* bricks = texture_create("res/wall.jpg");

    mesh_set_scale(wall1, 2, 1, 1);
    mesh_set_scale(wall2, 2, 1, 1);
    mesh_set_scale(wall3, 2, 1, 1);
    mesh_set_scale(wall4, 2, 1, 1);
    mesh_set_scale(ground, 4, 4, 4);

    mesh_set_rotation(wall2, 0, 90, 0);
    mesh_set_rotation(wall4, 0, 90, 0);

    mesh_set_position(cube1, -3, 1, -3);
    mesh_set_position(cube2, 3, 1, -3);
    mesh_set_position(cube3, -3, 1, 3);
    mesh_set_position(cube4, 3, 1, 3);

    mesh_set_position(wall1, 0, 1, -4);
    mesh_set_position(wall2, -4, 1, 0);
    mesh_set_position(wall3, 0, 1, 4);
    mesh_set_position(wall4, 4, 1, 0);

    //camera_setPosition(camera, 3, 5, 7);

    while (window_is_open(window))
    {
        static float t = 0.0f;

        camera_set_position(camera, sinf(t) * 7, 4, cosf(t) * 7);

        mesh_set_rotation(wall2, 0, t * 1000, 0);
        mesh_set_rotation(wall4, 0, t * 1000, 0);

        window_update(window);
        window_clear(0.0f, 0.0f, 0.0f);

        texture_bind(crate);
        mesh_draw(cube1, 36);
        mesh_draw(cube2, 36);
        mesh_draw(cube3, 36);
        mesh_draw(cube4, 36);

        texture_bind(grass);
        mesh_draw(ground, 6);

        texture_bind(bricks);
        mesh_draw(wall1, 6);
        mesh_draw(wall2, 6);
        mesh_draw(wall3, 6);
        mesh_draw(wall4, 6);

        camera_look_at(camera, 0, 0, 0);

        window_swap_buffers(window);
        t += 0.005f;
    }

    mesh_destroy(wall1);
    mesh_destroy(wall2);
    mesh_destroy(wall3);
    mesh_destroy(wall4);
    mesh_destroy(cube1);
    mesh_destroy(cube2);
    mesh_destroy(cube3);
    mesh_destroy(cube4);
    mesh_destroy(ground);

    texture_destroy(crate);
    texture_destroy(grass);
    texture_destroy(bricks);

    shader_destroy();

    glcontext_destroy(window);
    window_destroy(window);

    exit(0);
}