#ifndef MESH_H
#define MESH_H

#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include "Shader.h"
#include "Vector.h"

struct Vertex
{
    struct Vector3f position;
    struct Vector2f textureCoordinates;
    struct Vector3f normal;
};

struct Mesh
{
    unsigned int vertexArray;
    unsigned int vertexBuffer;
    unsigned int vertexCount;
    struct Vector3f position;
    struct Vector3f scale;
    struct Vector3f rotation;
};

enum MeshError
{
    MESH_MALLOC_FAILED = 1,
    MESH_MALLOC_VERTEX_BUFFER_FAILED,
    MESH_MALLOC_VERTEX_BUFFERS_FAILED,
    MESH_MALLOC_VERTEX_ARRAY_FAILED,
    MESH_MALLOC_VERTEX_ARRAYS_FAILED,
    MESH_MALLOC_ELEMENT_BUFFER_FAILED,
    MESH_MALLOC_ELEMENT_BUFFERS_FAILED
};

struct Mesh* mesh_create(float* vertices, unsigned int size);
struct Mesh* mesh_load(char* path);
void mesh_set_position(struct Mesh* mesh, float x, float y, float z);
void mesh_set_scale(struct Mesh* mesh, float x, float y, float z);
void mesh_set_rotation(struct Mesh* mesh, float x, float y, float z);
void mesh_draw(struct Mesh* mesh, struct Shader* shader);
void mesh_destroy(struct Mesh* mesh);

#endif // !MESH_H
