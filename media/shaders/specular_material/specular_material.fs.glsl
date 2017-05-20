
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


/*
#version 430 core

layout (location = 0) out vec4 color;

in vec3 vs_worldpos;
in vec3 vs_normal;

uniform vec4 color_ambient = vec4(0.5, 0.5, 0.1, 1.0);
uniform vec4 color_diffuse = vec4(0.6, 0.5, 0.1, 1.0);
uniform vec4 color_specular = vec4(1.0, 1.0, 1.0, 1.0);
uniform float shininess = 77.0f;

uniform vec3 light_pos;

void main(void)
{
    vec3 light_direction = normalize(light_pos - vs_worldpos);
    vec3 normal = normalize(vs_normal);
    vec3 half_vector = normalize(light_direction + normalize(vs_worldpos));
    float diffuse = max(0.0, dot(normal, light_direction));
    float specular = pow(max(0.0, dot(vs_normal, half_vector)), shininess);
    color = color_ambient + diffuse * color_diffuse + specular * color_specular;
};
*/