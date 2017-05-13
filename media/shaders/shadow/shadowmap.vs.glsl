#version 430 core

layout(location = 0) in vec3 vPosition;

out vec4 ShadowCoord;

uniform mat4 mvp;
uniform mat4 bias_mvp;

void main(){

	gl_Position =  mvp * vec4(vPosition,1);
	ShadowCoord = bias_mvp * vec4(vPosition,1);
	
}


