#include "Camera.h"
#include "Shader.h"
#include "Vector.h"
#include "Transform.h"

struct Camera* camera_create(float fov, float ratio)
{
    struct Camera* camera = malloc(sizeof(struct Camera));

    if (camera == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for the camera!");
        exit(CAMERA_MALLOC_FAILED);
    }

    camera->x       = 0.0f;
    camera->y       = 0.0f;
    camera->z       = 0.0f;
    camera->fov     = fov;
    camera->ratio   = ratio;

    return camera;
}

void camera_set_position(struct Camera* camera, float x, float y, float z)
{
    camera->x = x;
    camera->y = y;
    camera->z = z;
}

void camera_look_at(struct Camera* camera, float look_x, float look_y, float look_z)
{
    float view[4][4];
    transform_identity(view);
    
    float side[3] = { 0.0f, 0.0f, 0.0f };
    float forward[3] = { 0.0f, 0.0f, 0.0f };

    float eye[3] = { camera->x, camera->y, camera->z };
    float at[3]  = { look_x, look_y, look_z };
    float up[3]  = { 0.0f, 1.0f, 0.0f };

    vector_sub(eye, at, forward);
    vector_normalize(forward);

    vector_cross(up, forward, side);
    vector_normalize(side);

    vector_cross(forward, side, up);

    view[0][0] = side[0];
    view[1][0] = side[1];
    view[2][0] = side[2];

    view[0][1] = up[0];
    view[1][1] = up[1];
    view[2][1] = up[2];

    view[0][2] = forward[0];
    view[1][2] = forward[1];
    view[2][2] = forward[2];

    view[3][0] = vector_dot(side, eye);
    view[3][1] = vector_dot(up, eye);
    view[3][2] = vector_dot((float[3]) { -forward[0], -forward[1], -forward[2] }, eye);

    unsigned int viewLocation = glGetUniformLocation(shader->program, "view");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, (float*)view);

    float projection[4][4];

    for (unsigned int i = 0; i < 4; i++)
        for (unsigned int j = 0; j < 4; j++)
            projection[i][j] = 0.0f;

    projection[0][0] = 1.0f / (camera->ratio * tanf(camera->fov * (float)M_PI / 180.0f / 2));
    projection[1][1] = 1.0f / tanf(camera->fov * (float)M_PI / 180.0f / 2);
    projection[2][2] = -((100.0f + 0.1f) / (100.0f - 0.1f));
    projection[2][3] = -1.0f;
    projection[3][2] = -((2.0f * 100.0f * 0.1f) / (100.0f - 0.1f));

    unsigned int projectionLocation = glGetUniformLocation(shader->program, "projection");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, (float*)projection);
}

void camera_destroy(struct Camera* camera)
{
    free(camera);
}