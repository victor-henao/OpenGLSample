#version 420 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoordinates;
//layout (location = 2) in vec2 normal;

out vec2 _textureCoordinates;
out vec3 _normal;
//out vev3 _fragmentPosition;

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
    gl_Position = projection * view * transform * vec4(position.x, position.y, position.z, 1.0);
    _textureCoordinates = textureCoordinates;
    //_normal = Normal;
}