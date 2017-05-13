#version 430 core

layout(location = 0) in vec3 vPosition;

uniform mat4 mvp;

out vec4 vertex_position;

void main(){
	vertex_position = vec4(vPosition, 1.0f);

	gl_Position = mvp * vec4(vPosition, 1.0f);
}
