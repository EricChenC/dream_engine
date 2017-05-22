#version 430 core

layout (location = 0) out vec4 color; 

in TES_OUT
{
    vec3 out_N;
	vec3 out_L;
	vec3 out_V;  
} fs_in; 

uniform vec3 diffuse_albedo = vec3(0.5, 0.2, 0.7);
uniform vec3 specular_albedo = vec3(0.7);
uniform float specular_power = 128.0;
uniform vec3 ambient = vec3(0.1, 0.1, 0.1);

void main(void)
{
   // Normalize the incoming N, L and V vectors
    vec3 N = normalize(fs_in.out_N);
    vec3 L = normalize(fs_in.out_L);
    vec3 V = normalize(fs_in.out_V);

    // Calculate R locally
    vec3 R = reflect(-L, N);

    // Compute the diffuse and specular components for each fragment
    vec3 diffuse = max(dot(N, L), 0.0) * diffuse_albedo;
    vec3 specular = pow(max(dot(R, V), 0.0), specular_power) * specular_albedo;

    // Write final color to the framebuffer
    color = vec4(ambient + diffuse + specular, 1.0);
};
