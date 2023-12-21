#version 150 core

out vec4 out_Color;

uniform vec3 lightPosition;
in vec3 normal;
in vec3 worldPos;

void main(void)
{
    vec3 L = normalize(lightPosition - worldPos);
    vec3 N = normalize(normal);
	out_Color = vec4(1.0, 0.0, 0.0, 1.0);
}
