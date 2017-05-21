#version 430 core

layout(location = 0) in vec3 vPosition;
layout(location = 2) in vec3 vNormal;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

out vec4 out_vposition;
out vec4 out_normal;

void main(){
	out_vposition = vec4(vPosition, 1.0f);
	out_normal = vec4(vNormal, 1.0f);

	gl_Position = p * v * m * vec4(vPosition, 1.0f);
}




