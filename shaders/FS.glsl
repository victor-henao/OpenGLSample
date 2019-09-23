#version 420 core

in vec2 _textureCoordinates;
in vec3 _normal;
in vec3 _fragmentPosition;

out vec4 color;

uniform sampler2D image;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 cameraPosition;

void main()
{
    float ambientStrength = 0.0;
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 normalized = normalize(_normal);
    vec3 lightDirection = normalize(lightPosition - _fragmentPosition);
    float diffuseFactor = max(dot(normalized, lightDirection), 0.0);
    vec3 diffuse = diffuseFactor * lightColor;
    
    vec3 cameraDirection = normalize(cameraPosition - _fragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, normalized);
    
    float specularStrength = 1.0;
    float specularFactor = pow(max(dot(cameraDirection, reflectDirection), 0.0), 256);
    vec3 specular = specularStrength * specularFactor * lightColor;
    
    vec3 light = ambient + diffuse + specular;
    color = texture(image, _textureCoordinates) + vec4(light, 1.0);
}