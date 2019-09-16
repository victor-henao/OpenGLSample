#include "Camera.h"
#include "Shader.h"
#include "Vector.h"

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

    //mat4 view;
    //glm_mat4_identity(view);
    //glm_lookat((vec3) { camera->x, camera->y, camera->z }, (vec3) { 0, 0, 0 }, (vec3) { 0, 1, 0 }, view);

    //unsigned int viewLocation = glGetUniformLocation(shader->program, "view");
    //glUniformMatrix4fv(viewLocation, 1, GL_FALSE, (float*)view);

    //mat4 projection;
    //glm_perspective(glm_rad(camera->fov), camera->ratio, 0.1f, 100.0f, projection);

    //unsigned int projectionLocation = glGetUniformLocation(shader->program, "projection");
    //glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, (float*)projection);

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
    glm_mat4_identity(view);
    
    float axis_x[3];
    float axis_y[3];
    float axis_z[3];

    float eye[3] = { camera->x, camera->y, camera->z };
    float at[3]  = { look_x, look_y, look_z };
    float up[3]  = { 0.0f, 1.0f, 0.0f };

    vector_sub(eye, at, axis_z);
    vector_normalize(axis_z);

    vector_cross(axis_z, up, axis_x);
    vector_normalize(axis_x);

    vector_cross(axis_x, axis_z, axis_y);

    vector_negate(axis_z);

    view[0][0] = axis_x[0];
    view[0][1] = axis_x[1];
    view[0][2] = axis_x[2];
    view[0][3] = -vector_dot(axis_x, eye);

    view[1][0] = axis_y[0];
    view[1][1] = axis_y[1];
    view[1][2] = axis_y[2];
    view[1][3] = -vector_dot(axis_y, eye);

    view[2][0] = axis_z[0];
    view[2][1] = axis_z[1];
    view[2][2] = axis_z[2];
    view[2][3] = -vector_dot(axis_z, eye);

    view[3][0] = 0.0f;
    view[3][1] = 0.0f;
    view[3][2] = 0.0f;
    view[3][3] = 1.0f;

    glm_lookat((vec3) { camera->x, camera->y, camera->z }, (vec3) { look_x, look_y, look_z }, (vec3) { 0, 1, 0 }, view);

    unsigned int viewLocation = glGetUniformLocation(shader->program, "view");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, (float*)view);

    float projection[4][4];

    for (unsigned int i = 0; i < 4; i++)
        for (unsigned int j = 0; j < 4; j++)
            projection[i][j] = 0.0f;

    projection[0][0] = 1.0f / (camera->ratio * tanf(glm_rad(camera->fov) / 2));
    projection[1][1] = 1.0f / tanf(glm_rad(camera->fov) / 2);
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