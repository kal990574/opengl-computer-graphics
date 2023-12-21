#version 150 core

out vec4 out_Color;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;
uniform vec3 diffColor;
uniform vec3 specColor;
uniform float shininess;
in vec3 normal;
in vec3 worldPos;

void main(void)
{
    vec3 toLight = lightPosition - worldPos;
    vec3 L = normalize(toLight);
    vec3 N = normalize(normal);
    vec3 V = normalize(cameraPosition - worldPos);
    vec3 R = reflect(-L, N);
    vec3 Ii = vec3(100,100,100)/dot(toLight,toLight);
    vec3 color = diffColor * 0.0 + Ii * (diffColor*max(0,dot(N,L)) + specColor*pow(max(0,dot(R,V)),100));
	out_Color = vec4(pow(color,vec3(1/2.2)), 1.0);
}
