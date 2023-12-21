#version 410 core

layout(location=0) in vec3 in_Position;
layout(location=1) in vec3 in_Normal;
uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 posWorld;
out vec3 posCamera;
out vec3 normal;
out vec3 worldPos;
void main(void)
{
    normal = (modelMat * vec4(in_Normal,0)).xyz;
    worldPos = (modelMat * vec4(in_Position, 1)).xyz;
    gl_Position = projMat * viewMat * modelMat * vec4(in_Position, 1);
}

