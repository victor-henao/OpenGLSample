#version 420 core

in vec2 _textureCoordinates;
//in vec3 _normal;

out vec4 color;

uniform sampler2D image;
//uniform vec3 lightPosition;

void main()
{
    //color = vec4(0.0, 1.0, 0.0, 1.0);
    color = texture(image, _textureCoordinates);
    
}