#ifndef CAMERA_H
#define CMAERA_H

#include "Shader.h"
#include "Vector.h"

struct Camera
{
    struct Vector3f position;
    float fov;
    float ratio;
};

enum CameraError
{
    CAMERA_MALLOC_FAILED = 1
};

struct Camera* camera_create(float fov, float ratio);
void camera_set_position(struct Camera* camera, float x, float y, float z);
void camera_look_at(struct Camera* camera, struct Shader* shader, float x, float y, float z);
void camera_destroy(struct Camera* camera);

#endif // !CAMERA_H
