#version 430 core

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 normal;

out vec3 vs_worldpos;
out vec3 vs_normal;

void main(void)
{
    vec4 position = p * v * m * vec4(position, 1.0f);
    gl_Position = position;
    vs_worldpos = position.xyz;
    vs_normal = mat3(m) * normal;
}
