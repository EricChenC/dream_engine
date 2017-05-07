#version 430 core

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vUV;
layout(location = 2) in vec3 vNormal;

uniform mat4 mvp;
uniform mat4 mv;

out vec4 mv_vposition;
out vec4 mv_normal;

void main(){

	mv_vposition = vec4(vPosition, 1.0f);
	mv_normal = vec4(vNormal, 1.0f);

	gl_Position = mvp * vec4(vPosition, 1.0f);
}
