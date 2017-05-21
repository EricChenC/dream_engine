#version 430 core

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

layout (location = 0) in vec3 position;
layout (location = 2) in vec3 normal;

out vec3 out_N;
out vec3 out_L;
out vec3 out_V;

uniform vec3 light_pos;

void main(void)
{
   // Calculate view-space coordinate
    vec4 pos = v * m * vec4(position, 1.0f);

    // Calculate normal in view-space
    out_N = mat3(v * m) * normal;

    // Calculate light vector
    out_L = light_pos - pos.xyz;

    // Calculate view vector
    out_V = -pos.xyz;

    // Calculate the clip-space position of each vertex
    gl_Position = p * pos;
}
