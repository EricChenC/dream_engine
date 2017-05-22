#version 430 core                                                                 
 
layout (vertices = 3) out; 

in VS_OUT                                                                         
{                                                                                 
    vec3 out_N;
	vec3 out_L;
	vec3 out_V;  
} tcs_in[];  

out TCS_OUT                                                                         
{                                                                                 
    vec3 out_N;
	vec3 out_L;
	vec3 out_V;  
} tcs_out[];                                                                                                                   
 
void main(void)                                                                   
{                                                                                 
    if (gl_InvocationID == 0)                                                     
    {                                                                             
        gl_TessLevelInner[0] = 20.0;
		
        gl_TessLevelOuter[0] = 20.0;                                               
        gl_TessLevelOuter[1] = 20.0;                                               
        gl_TessLevelOuter[2] = 20.0;                                               
    }   

	tcs_out[gl_InvocationID].out_N = tcs_in[gl_InvocationID].out_N;
	tcs_out[gl_InvocationID].out_L = tcs_in[gl_InvocationID].out_L;
	tcs_out[gl_InvocationID].out_V = tcs_in[gl_InvocationID].out_V;
	
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;     
}                                                                                 