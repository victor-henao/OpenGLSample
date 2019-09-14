#version 420 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textureCoordinates;

out vec3 _color;
out vec2 _textureCoordinates;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * transform * vec4(position.x, position.y, position.z, 1.0);
    _color = color;
    _textureCoordinates = textureCoordinates;
}