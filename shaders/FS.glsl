#version 420 core

in vec2 _textureCoordinates;
in vec3 _normal;
in vec3 _fragmentPosition;

out vec4 color;

uniform sampler2D image;
uniform vec3 lightPosition;
uniform vec3 lightColor;

void main()
{
    float ambientStrength = 1.0;
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 normalized = normalize(_normal);
    vec3 lightDirection = normalize(lightPosition - _fragmentPosition);
    float diffuseFactor = max(dot(normalized, lightDirection), 0.0);
    vec3 diffuse = diffuseFactor * lightColor;
    
    vec3 light = diffuse;
    color = texture(image, _textureCoordinates) + vec4(light, 1.0);
}