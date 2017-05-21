#version 430 core

in vec4 out_vposition;
in vec4 out_normal;
in vec4 out_light_pos;

out vec4 color;

void main(){
	vec4 ambient = vec4(0.5f, 0.0f, 0.0f, 1.0f);

	vec4 dir =  out_light_pos - out_vposition;
	float angle = max(0.0f, dot(normalize(dir),normalize(out_normal)));

	color = ambient + vec4(angle);
}


