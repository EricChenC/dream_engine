#version 430 core

uniform vec3 light_pos;

in vec4 mv_vposition;
in vec4 mv_normal;

out vec4 color;

void main(){
	vec4 dir = vec4(light_pos,1.0f) - mv_vposition;

	float angle = dot(normalize(dir),normalize(mv_normal));

	color = vec4(angle);
}