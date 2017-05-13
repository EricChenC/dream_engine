#version 430 core

uniform vec4 light_position;

in vec4 vertex_position;

out vec4 color;

void main(){
	
	vec4 vertex_dirction = light_position - vertex_position;

	// dot need a vertor is oppsited
	float angle = dot(normalize(light_position), normalize(vertex_dirction));
	
	vec4 light_color = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	vec4 ambient_color = vec4(0.4f, 0.4f, 0.4f, 1.0f);
	
	if(angle > 0.98f){
		light_color = vec4(0.9f, 0.9f ,0.9f, 1.0f);
	}
	
	color = ambient_color + light_color;
	
}