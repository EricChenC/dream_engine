#version 430 core

layout(location = 0) in vec3 vPosition;
layout(location = 2) in vec3 vNormal;

uniform mat4 mvp;
uniform mat4 mv;

out vec4 out_vposition;
out vec4 out_normal;

void main(){
	out_vposition = mv * vec4(vPosition, 1.0f);
	out_normal = mv * vec4(vNormal, 1.0f);

	gl_Position = mvp * vec4(vPosition, 1.0f);
}