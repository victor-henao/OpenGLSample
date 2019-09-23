#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "Shader.h"

struct Shader* shader_create(char* vertexShaderPath, char* fragmentShaderPath)
{
    struct Shader* shader = malloc(sizeof(struct Shader));

    if (shader == NULL)
    {
        fprintf(stderr, "Failed to allocate memory for the shader!");
        exit(SHADER_MALLOC_FAILED);
    }

    shader->vertexShader = shader_compile(GL_VERTEX_SHADER, vertexShaderPath);
    shader->fragmentShader = shader_compile(GL_FRAGMENT_SHADER, fragmentShaderPath);

    shader->program = glCreateProgram();

    glAttachShader(shader->program, shader->vertexShader);
    glAttachShader(shader->program, shader->fragmentShader);

    glLinkProgram(shader->program);
    //glUseProgram(shader->program);

    glDetachShader(shader->program, shader->vertexShader);
    glDetachShader(shader->program, shader->fragmentShader);

    glDeleteShader(shader->vertexShader);
    glDeleteShader(shader->fragmentShader);

    return shader;
}

unsigned int shader_compile(unsigned int type, char* path)
{
    unsigned int id = glCreateShader(type);
    const char* source = shader_read_file(path);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);
    free((char*)source);

    int compiled;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compiled);

    if (compiled == GL_FALSE)
    {
        fprintf(stderr, "Failed to compile shader!\n");

        unsigned int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &(int)length);
        char* message = malloc(sizeof(length));
        glGetShaderInfoLog(id, (int)length, &(int)length, message);
        printf("%s", message);
        free(message);
    }

    return id;
}

char* shader_read_file(char* path)
{
    FILE* file = fopen(path, "rb");

    if (file == NULL)
    {
        fprintf(stderr, "Failed to open shader file!");
        exit(SHADER_OPEN_FILE_FAILED);
    }

    fseek(file, 0, SEEK_END);
    unsigned long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* content = malloc(size + 1);

    if (content == NULL)
    {
        fprintf(stderr, "Failed to read content from shader file!");
        exit(SHADER_READ_FAILED);
    }

    fread(content, 1, size, file);
    fclose(file);

    content[size] = '\0';

    return content;
}

void shader_destroy(struct Shader* shader)
{
    glDeleteProgram(shader->program);

    free(shader);
}