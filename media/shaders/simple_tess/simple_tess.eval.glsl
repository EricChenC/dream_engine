#version 430 core                                                                 

layout (triangles, equal_spacing, cw) in; 

in TCS_OUT
{
    vec3 out_N;
	vec3 out_L;
	vec3 out_V;
} tes_in[];

out TES_OUT
{
    vec3 out_N;
	vec3 out_L;
	vec3 out_V;
} tes_out;                          

void main(void)                                                                   
{  
	tes_out.out_N = tes_in[0].out_N;
	tes_out.out_L = tes_in[0].out_L;
	tes_out.out_V = tes_in[0].out_V;
	
    gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position) +                       
                  (gl_TessCoord.y * gl_in[1].gl_Position) +                       
                  (gl_TessCoord.z * gl_in[2].gl_Position);                        
}                                                                                 