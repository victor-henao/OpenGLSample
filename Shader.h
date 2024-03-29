#ifndef SHADER_H
#define SHADER_H

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

struct Shader* shader_create(char* vertexShaderPath, char* fragmentShaderPath);
unsigned int shader_compile(unsigned int type, char* path);
char* shader_read_file(char* path);
void shader_destroy(struct Shader* shader);

#endif // !SHADER_H
