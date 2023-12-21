#version 150 core

out vec4 out_Color;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform vec3 diffColor;
uniform vec3 specColor;
uniform float shininess;
uniform sampler2D diffTex;
in vec3 normal;
in vec3 worldPos;
in vec2 texCoord;

void main(void)
{
    vec3 toLight = lightPosition - worldPos;
    vec3 L = normalize(toLight);
    vec3 N = normalize(normal);
    vec3 V = normalize(cameraPosition - worldPos);
    vec3 R = reflect(-L, N);
    vec3 Ii = vec3(200,200,200)/dot(toLight,toLight);
    vec3 dColor = texture(diffTex, texCoord).xyz;
    vec3 color = Ii * (dColor*max(0,dot(N,L)) + specColor*pow(max(0,dot(R,V)),shininess));
	out_Color = vec4(pow(color,vec3(1/2.2)), 1.0);
}
