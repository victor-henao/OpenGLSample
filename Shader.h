#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>

struct Shader
{
    unsigned int program;
    unsigned int vertexShader;
    unsigned int fragmentShader;
};

enum ShaderError
{
    SHADER_MALLOC_FAILED = 1,
    SHADER_OPEN_FILE_FAILED,
    SHADER_READ_FAILED
};

struct Shader* shader;

void shader_initialize(char* vertexShaderSource, char* fragmentShaderSource);
unsigned int shader_compile(unsigned int type, char* path);
char* shader_read_file(char* path);
void shader_destroy();

#endif // !SHADER_H
