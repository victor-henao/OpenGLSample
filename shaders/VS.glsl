#version 420 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinates;
layout (location = 2) in vec3 normal;

out vec2 _textureCoordinates;
out vec3 _normal;
out vec3 _fragmentPosition;

mat4 transform;

mat4 rotation;
uniform mat4 rotationX;
uniform mat4 rotationY;
uniform mat4 rotationZ;

uniform mat4 translation;
uniform mat4 scale;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    rotation = rotationX * rotationY * rotationZ;
    transform = translation * rotation * scale;
    _fragmentPosition = vec3(transform * vec4(position, 1.0));
    gl_Position = projection * view * vec4(_fragmentPosition, 1.0);
    
    _textureCoordinates = textureCoordinates;
    _normal = mat3(transpose(inverse(transform))) * normal;
}