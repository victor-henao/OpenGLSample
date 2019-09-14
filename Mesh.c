#include "Mesh.h"
#include "Shader.h"
#include "Transform.h"

struct Mesh* mesh_create(float* vertices, unsigned int size, unsigned int* elements, unsigned int elementSize)
{
    struct Mesh* mesh = malloc(sizeof(struct Mesh));

    if (mesh == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for the object!");
        exit(MESH_MALLOC_FAILED);
    }

    glGenVertexArrays(1, &mesh->vertexArray);
    glBindVertexArray(mesh->vertexArray);

    glGenBuffers(1, &mesh->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &mesh->elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementSize, elements, GL_STATIC_DRAW);

    mesh->x = 0.0f;
    mesh->y = 0.0f;
    mesh->z = 0.0f;

    mesh->scale_x = 1.0f;
    mesh->scale_y = 1.0f;
    mesh->scale_z = 1.0f;

    mesh->rotation_x = 0.0f;
    mesh->rotation_y = 0.0f;
    mesh->rotation_z = 0.0f;

    return mesh;
}

void mesh_translate(struct Mesh* mesh, float x, float y, float z)
{
    mesh->x += x;
    mesh->y += y;
    mesh->z += z;
}

void mesh_rotate(struct Mesh* mesh, float x, float y, float z)
{
    mesh->rotation_x += x;
    mesh->rotation_y += y;
    mesh->rotation_z += z;
}

void mesh_set_position(struct Mesh* mesh, float x, float y, float z)
{
    mesh->x = x;
    mesh->y = y;
    mesh->z = z;
}

void mesh_set_scale(struct Mesh* mesh, float scale_x, float scale_y, float scale_z)
{
    mesh->scale_x = scale_x;
    mesh->scale_y = scale_y;
    mesh->scale_z = scale_z;
}

void mesh_set_rotation(struct Mesh* mesh, float x, float y, float z)
{
    mesh->rotation_x = x;
    mesh->rotation_y = y;
    mesh->rotation_z = z;
}

void mesh_draw(struct Mesh* mesh, unsigned int verticesCount)
{
    float transform[4][4];
    transform_identity(transform);

    transform_translate(transform, (float[3]) { mesh->x, mesh->y, mesh->z }); // OK

    glm_rotate(transform, glm_rad(mesh->rotation_x), (vec3) { 1.0f, 0.0f, 0.0f });
    glm_rotate(transform, glm_rad(mesh->rotation_y), (vec3) { 0.0f, 1.0f, 0.0f });
    glm_rotate(transform, glm_rad(mesh->rotation_z), (vec3) { 0.0f, 0.0f, 1.0f });

    //matrix_rotate(transform, mesh->rotation_x, (float[3]) { 1.0f, 0.0f, 0.0f });
    //matrix_rotate(transform, mesh->rotation_y, (float[3]) { 0.0f, 1.0f, 0.0f });
    //matrix_rotate(transform, mesh->rotation_z, (float[3]) { 0.0f, 0.0f, 1.0f });

    glm_scale(transform, (vec3) { mesh->scale_x, mesh->scale_y, mesh->scale_z });
    //matrix_scale(transform, (float[3]) { mesh->scale_x, mesh->scale_y, mesh->scale_z });

    unsigned int transformLocation = glGetUniformLocation(shader->program, "transform");
    glUniformMatrix4fv(transformLocation, 1, GL_FALSE, (float*)transform);

    glBindVertexArray(mesh->vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->elementBuffer);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, 0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void mesh_destroy(struct Mesh* mesh)
{
    glDeleteVertexArrays(1, &mesh->vertexArray);
    glDeleteBuffers(1, &mesh->vertexBuffer);
    glDeleteBuffers(1, &mesh->elementBuffer);

    free(mesh);
}