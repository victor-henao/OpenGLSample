#version 420 core

in vec3 _color;
in vec2 _textureCoordinates;

out vec4 color;

uniform sampler2D image;

void main()
{
    //color = vec4(_color, 1.0f);
    color = texture(image, _textureCoordinates);
    //color = texture(image2, _textureCoordinates);
}