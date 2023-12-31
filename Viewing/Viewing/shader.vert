#version 410 core

layout(location=0) in vec3 in_Position;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main(void)
{
    gl_Position = projMat * viewMat * modelMat * vec4(in_Position, 1);
}

