#version 430 core

uniform mat4 mvp;
uniform mat4 bias_mvp;

layout(location = 0) in vec3 vPosition;

out vec4 ShadowCoord;

void main(){

	gl_Position =  mvp * vec4(vPosition,1);
	ShadowCoord = bias_mvp * vec4(vPosition,1);
	
}


