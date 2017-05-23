#version 430 core 

uniform mat4 mvp;
                                                                  
void main(void)                                                   
{                                                                
    const vec4 vertices[] = vec4[](vec4( 0.5, -0.5, 0.5, 1.0), 
								   vec4( -0.5, -0.5, 0.5, 1.0),
								   vec4( -0.5, 0.5, 0.5, 1.0),
                                   vec4( 0.5, 0.5, 0.5, 1.0)
								  ); 
                                                                  
    gl_Position = mvp * vertices[gl_VertexID];    

}                                                                 