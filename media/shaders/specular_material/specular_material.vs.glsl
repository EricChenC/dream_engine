#version 430 core

layout(location = 0) in vec3 vPosition;
layout(location = 2) in vec3 vNormal;

uniform mat4 m;
uniform mat4 v;
uniform mat4 p;
uniform vec3 light_pos;

out vec4 out_vposition;
out vec4 out_normal;
out vec4 out_light_pos;

void main(){
	out_vposition = v * m * vec4(vPosition, 1.0f);
	out_normal = v * m * vec4(vNormal, 1.0f);
	out_light_pos = v *m * vec4(light_pos, 1.0f);

	gl_Position = p * v * m * vec4(vPosition, 1.0f);
}




