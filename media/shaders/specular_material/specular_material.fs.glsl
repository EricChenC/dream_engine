#version 430 core

uniform vec3 light_pos;

in vec4 out_vposition;
in vec4 out_normal;

out vec4 color;

void main(){
	vec4 ambient = vec4(0.5f, 0.0f, 0.0f, 1.0f);

	vec4 dir = vec4(light_pos,1.0f) - out_vposition;
	float light_len = length(dir);
	
	dir = dir / light_len;

	float angle = max(0.0f, dot(normalize(dir),normalize(out_normal)));

	color = ambient + vec4(angle);
}


