#version 430 core

layout(location = 0) in vec3 vPosition;

// instanced position
layout(location = 4) in vec3 instanced_pos;

uniform mat4 mvp;

out vec4 vert_color;

void main(){
	vert_color = vec4((instanced_pos + vPosition), 0.8f);
	gl_Position = mvp * vec4((instanced_pos + vPosition), 1.0f);
}
