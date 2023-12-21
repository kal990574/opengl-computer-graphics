#version 150 core

out vec4 out_Color;

uniform vec3 lightPosition;
uniform vec3 cameraPosition;
in vec3 normal;
in vec3 worldPos;

void main(void)
{
    vec3 L = normalize(lightPosition - worldPos);
    vec3 N = normalize(normal);
    vec3 color = vec3(0,1,0) * dot(N,L);
	out_Color = vec4(color, 1.0);
}
