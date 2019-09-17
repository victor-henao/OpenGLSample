#include "Mesh.h"
#include "Shader.h"
#include "Matrix.h"

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

    for (unsigned int i = 0; i < 3; i++)
    {
        mesh->position[i] = 0.0f;
        mesh->scale[i] = 1.0f;
        mesh->rotation[i] = 0.0f;
    }

    return mesh;
}

void mesh_translate(struct Mesh* mesh, float x, float y, float z)
{
    mesh->position[0] += x;
    mesh->position[1] += y;
    mesh->position[2] += z;
}

void mesh_rotate(struct Mesh* mesh, float x, float y, float z)
{
    mesh->rotation[0] += x;
    mesh->rotation[1] += y;
    mesh->rotation[2] += z;
}

void mesh_set_position(struct Mesh* mesh, float x, float y, float z)
{
    mesh->position[0] = x;
    mesh->position[1] = y;
    mesh->position[2] = z;
}

void mesh_set_scale(struct Mesh* mesh, float x, float y, float z)
{
    mesh->scale[0] = x;
    mesh->scale[1] = y;
    mesh->scale[2] = z;
}

void mesh_set_rotation(struct Mesh* mesh, float x, float y, float z)
{
    mesh->rotation[0] = x;
    mesh->rotation[1] = y;
    mesh->rotation[2] = z;
}

void mesh_draw(struct Mesh* mesh, unsigned int verticesCount)
{
    float rotation_x[4][4];
    float rotation_y[4][4];
    float rotation_z[4][4];
    float translation[4][4];
    float scale[4][4];

    matrix_identity(rotation_x);
    matrix_identity(rotation_y);
    matrix_identity(rotation_z);
    matrix_identity(translation);
    matrix_identity(scale);

    matrix_rotate(rotation_x, mesh->rotation[0], 'x');
    matrix_rotate(rotation_y, mesh->rotation[1], 'y');
    matrix_rotate(rotation_z, mesh->rotation[2], 'z');

    matrix_translate(translation, mesh->position);

    matrix_scale(scale, mesh->scale);

    unsigned int rotationXLocation = glGetUniformLocation(shader->program, "rotation_x");
    glUniformMatrix4fv(rotationXLocation, 1, GL_FALSE, (float*)rotation_x);

    unsigned int rotationYLocation = glGetUniformLocation(shader->program, "rotation_y");
    glUniformMatrix4fv(rotationYLocation, 1, GL_FALSE, (float*)rotation_y);

    unsigned int rotationZLocation = glGetUniformLocation(shader->program, "rotation_z");
    glUniformMatrix4fv(rotationZLocation, 1, GL_FALSE, (float*)rotation_z);

    unsigned int translationLocation = glGetUniformLocation(shader->program, "translation");
    glUniformMatrix4fv(translationLocation, 1, GL_FALSE, (float*)translation);

    unsigned int scaleLocation = glGetUniformLocation(shader->program, "scale");
    glUniformMatrix4fv(scaleLocation, 1, GL_FALSE, (float*)scale);

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