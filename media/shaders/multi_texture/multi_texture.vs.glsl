#version 430 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_tex_coord;

out vec2 tex_coord0;
out vec2 tex_coord1;

uniform float time;
uniform mat4 mvp;

void main(void)
{
    mat2 m = mat2( vec2(cos(time), sin(time)),
                   vec2(-sin(time), cos(time)) );
				   
    tex_coord0 = in_tex_coord * m;
    tex_coord1 = in_tex_coord * transpose(m);
	
	gl_Position = mvp * vec4(in_position, 1.0f);
}