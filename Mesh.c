#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include "Mesh.h"
#include "Shader.h"
#include "Matrix.h"

struct Mesh* mesh_create(float* vertices, unsigned int size)
{
    struct Mesh* mesh = malloc(sizeof(struct Mesh));

    if (mesh == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for the mesh!");
        exit(MESH_MALLOC_FAILED);
    }

    glGenVertexArrays(1, &mesh->vertexArray);
    glBindVertexArray(mesh->vertexArray);

    glGenBuffers(1, &mesh->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    mesh->position  = (struct Vector3f){ 0.0f, 0.0f, 0.0f };
    mesh->scale     = (struct Vector3f){ 1.0f, 1.0f, 1.0f };
    mesh->rotation  = (struct Vector3f){ 0.0f, 0.0f, 0.0f };

    return mesh;
}

struct Mesh* mesh_load(char* path)
{
    static unsigned int meshCount = 1;

    struct Mesh* mesh = malloc(sizeof(struct Mesh));

    if (mesh == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for the mesh!");
        exit(MESH_MALLOC_FAILED);
    }

    mesh->vertexCount = 0;

    FILE* file = fopen(path, "r");

    unsigned int positionCount  = 0;
    unsigned int textureCount   = 0;
    unsigned int normalCount    = 0;

    struct Vector3f* verticePositions           = malloc(sizeof(struct Vector3f));
    struct Vector2f* verticeTextureCoordinates  = malloc(sizeof(struct Vector2f));
    struct Vector3f* verticeNormals             = malloc(sizeof(struct Vector3f));
    struct Vertex* meshVertices                 = malloc(sizeof(struct Vertex));

    if (verticePositions == NULL || verticeTextureCoordinates == NULL || verticeNormals == NULL || meshVertices == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for the mesh!");
        exit(MESH_MALLOC_FAILED);
    }

    while (!feof(file))
    {
        char line[32];
        fscanf(file, "%s", line);

        if (strcmp(line, "v") == 0)
        {
            fscanf(file, "%f %f %f\n", &verticePositions[positionCount].x, &verticePositions[positionCount].y, &verticePositions[positionCount].z);
            positionCount++;

            struct Vector3f* tmp = realloc(verticePositions, sizeof(struct Vector3f) * (positionCount + 1));

            if (tmp == NULL)
            {
                fprintf(stderr, "Failed to allocate memory for the mesh!");
                exit(MESH_MALLOC_FAILED);
            }
            else
                verticePositions = tmp;
        }

        if (strcmp(line, "vt") == 0)
        {
            fscanf(file, "%f %f\n", &verticeTextureCoordinates[textureCount].x, &verticeTextureCoordinates[textureCount].y);
            textureCount++;

            struct Vector2f* tmp = realloc(verticeTextureCoordinates, sizeof(struct Vector2f) * (textureCount + 1));

            if (tmp == NULL)
            {
                fprintf(stderr, "Failed to allocate memory for the mesh!");
                exit(MESH_MALLOC_FAILED);
            }
            else
                verticeTextureCoordinates = tmp;
        }

        if (strcmp(line, "vn") == 0)
        {
            fscanf(file, "%f %f %f\n", &verticeNormals[normalCount].x, &verticeNormals[normalCount].y, &verticeNormals[normalCount].z);
            normalCount++;

            struct Vector3f* tmp = realloc(verticeNormals, sizeof(struct Vector3f) * (normalCount + 1));

            if (tmp == NULL)
            {
                fprintf(stderr, "Failed to allocate memory for the mesh!");
                exit(MESH_MALLOC_FAILED);
            }
            else
                verticeNormals = tmp;
        }

        if (strcmp(line, "f") == 0)
        {
            struct Vector3u vertexIndices;
            struct Vector3u textureCoordinateIndices;
            struct Vector3u normalIndices;

            fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
                &vertexIndices.x, &textureCoordinateIndices.x, &normalIndices.x,
                &vertexIndices.y, &textureCoordinateIndices.y, &normalIndices.y,
                &vertexIndices.z, &textureCoordinateIndices.z, &normalIndices.z
            );

            struct Vertex* tmp = realloc(meshVertices, sizeof(struct Vertex) * (mesh->vertexCount + 3));

            if (tmp == NULL)
            {
                fprintf(stderr, "Failed to allocate memory for the mesh!");
                exit(MESH_MALLOC_FAILED);
            }
            else
                meshVertices = tmp;

            meshVertices[mesh->vertexCount].position = verticePositions[vertexIndices.x - 1];
            meshVertices[mesh->vertexCount].textureCoordinates = verticeTextureCoordinates[textureCoordinateIndices.x - 1];
            meshVertices[mesh->vertexCount].normal = verticeNormals[normalIndices.x - 1];

            mesh->vertexCount += 1;

            meshVertices[mesh->vertexCount].position = verticePositions[vertexIndices.y - 1];
            meshVertices[mesh->vertexCount].textureCoordinates = verticeTextureCoordinates[textureCoordinateIndices.y - 1];
            meshVertices[mesh->vertexCount].normal = verticeNormals[normalIndices.y - 1];

            mesh->vertexCount += 1;

            meshVertices[mesh->vertexCount].position = verticePositions[vertexIndices.z - 1];
            meshVertices[mesh->vertexCount].textureCoordinates = verticeTextureCoordinates[textureCoordinateIndices.z - 1];
            meshVertices[mesh->vertexCount].normal = verticeNormals[normalIndices.z - 1];

            mesh->vertexCount += 1;
        }
    }

    printf("Number of vertices of mesh %u: %u\n", meshCount, mesh->vertexCount);
    meshCount++;

    fclose(file);

    free(verticePositions);
    free(verticeTextureCoordinates);
    free(verticeNormals);

    glGenVertexArrays(1, &mesh->vertexArray);
    glBindVertexArray(mesh->vertexArray);

    glGenBuffers(1, &mesh->vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(struct Vertex) * mesh->vertexCount, meshVertices, GL_STATIC_DRAW);

    free(meshVertices);

    mesh->position = (struct Vector3f){ 0.0f, 0.0f, 0.0f };
    mesh->scale    = (struct Vector3f){ 1.0f, 1.0f, 1.0f };
    mesh->rotation = (struct Vector3f){ 0.0f, 0.0f, 0.0f };

    return mesh;
}

void mesh_set_position(struct Mesh* mesh, float x, float y, float z)
{
    mesh->position.x = x;
    mesh->position.y = y;
    mesh->position.z = z;
}

void mesh_set_scale(struct Mesh* mesh, float x, float y, float z)
{
    mesh->scale.x = x;
    mesh->scale.y = y;
    mesh->scale.z = z;
}

void mesh_set_rotation(struct Mesh* mesh, float x, float y, float z)
{
    mesh->rotation.x = x;
    mesh->rotation.y = y;
    mesh->rotation.z = z;
}

void mesh_draw(struct Mesh* mesh, struct Shader* shader)
{
    float rotationX[4][4];
    float rotationY[4][4];
    float rotationZ[4][4];
    float translation[4][4];
    float scale[4][4];

    matrix_identity(rotationX);
    matrix_identity(rotationY);
    matrix_identity(rotationZ);
    matrix_identity(translation);
    matrix_identity(scale);

    matrix_rotate(rotationX, mesh->rotation.x, 'x');
    matrix_rotate(rotationY, mesh->rotation.y, 'y');
    matrix_rotate(rotationZ, mesh->rotation.z, 'z');

    matrix_translate(translation, (float[3]) { mesh->position.x, mesh->position.y, mesh->position.z });

    matrix_scale(scale, (float[3]) { mesh->scale.x, mesh->scale.y, mesh->scale.z });

    glUseProgram(shader->program);

    unsigned int rotationXLocation = glGetUniformLocation(shader->program, "rotationX");
    glUniformMatrix4fv(rotationXLocation, 1, GL_FALSE, (float*)rotationX);

    unsigned int rotationYLocation = glGetUniformLocation(shader->program, "rotationY");
    glUniformMatrix4fv(rotationYLocation, 1, GL_FALSE, (float*)rotationY);

    unsigned int rotationZLocation = glGetUniformLocation(shader->program, "rotationZ");
    glUniformMatrix4fv(rotationZLocation, 1, GL_FALSE, (float*)rotationZ);

    unsigned int translationLocation = glGetUniformLocation(shader->program, "translation");
    glUniformMatrix4fv(translationLocation, 1, GL_FALSE, (float*)translation);

    unsigned int scaleLocation = glGetUniformLocation(shader->program, "scale");
    glUniformMatrix4fv(scaleLocation, 1, GL_FALSE, (float*)scale);

    glBindVertexArray(mesh->vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));

    glDrawArrays(GL_TRIANGLES, 0, mesh->vertexCount);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void mesh_destroy(struct Mesh* mesh)
{
    glDeleteVertexArrays(1, &mesh->vertexArray);
    glDeleteBuffers(1, &mesh->vertexBuffer);

    free(mesh);
}