#ifndef MESH_H
#define MESH_H

#include <stdlib.h>
#include <GL/glew.h>
#include <cglm/cglm.h>

struct Mesh
{
    unsigned int vertexArray;
    unsigned int vertexBuffer;
    unsigned int elementBuffer;
    float x, y, z;
    float scale_x, scale_y, scale_z;
    float rotation_x, rotation_y, rotation_z;
};

enum ObjectError
{
    MESH_MALLOC_FAILED = 1,
    MESH_MALLOC_VERTEX_BUFFER_FAILED,
    MESH_MALLOC_VERTEX_BUFFERS_FAILED,
    MESH_MALLOC_VERTEX_ARRAY_FAILED,
    MESH_MALLOC_VERTEX_ARRAYS_FAILED,
    MESH_MALLOC_ELEMENT_BUFFER_FAILED,
    MESH_MALLOC_ELEMENT_BUFFERS_FAILED
};

struct Mesh* mesh_create(float* vertices, unsigned int size, unsigned int* elements, unsigned int elementSize);
void mesh_translate(struct Mesh* mesh, float x, float y, float z);
void mesh_rotate(struct Mesh* mesh, float x, float y, float z);
void mesh_set_position(struct Mesh* mesh, float x, float y, float z);
void mesh_set_scale(struct Mesh* mesh, float x, float y, float z);
void mesh_set_rotation(struct Mesh* mesh, float x, float y, float z);
void mesh_draw(struct Mesh* mesh, unsigned int verticesCount);
void mesh_destroy(struct Mesh* mesh);

#endif // !MESH_H
