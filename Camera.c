#include "Camera.h"
#include "Shader.h"

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

    mat4 view;
    glm_mat4_identity(view);
    glm_lookat((vec3) { camera->x, camera->y, camera->z }, (vec3) { 0, 0, 0 }, (vec3) { 0, 1, 0 }, view);

    unsigned int viewLocation = glGetUniformLocation(shader->program, "view");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, (float*)view);

    mat4 projection;
    glm_perspective(glm_rad(camera->fov), camera->ratio, 0.1f, 100.0f, projection);

    unsigned int projectionLocation = glGetUniformLocation(shader->program, "projection");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, (float*)projection);

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
    mat4 view;
    glm_mat4_identity(view);
    glm_lookat((vec3) { camera->x, camera->y, camera->z }, (vec3) { look_x, look_y, look_z }, (vec3) { 0, 1, 0 }, view);

    unsigned int viewLocation = glGetUniformLocation(shader->program, "view");
    glUniformMatrix4fv(viewLocation, 1, GL_FALSE, (float*)view);

    mat4 projection;
    glm_perspective(glm_rad(camera->fov), camera->ratio, 0.1f, 100.0f, projection);

    unsigned int projectionLocation = glGetUniformLocation(shader->program, "projection");
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, (float*)projection);
}

void camera_destroy(struct Camera* camera)
{
    free(camera);
}