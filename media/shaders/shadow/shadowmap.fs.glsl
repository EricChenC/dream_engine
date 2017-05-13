#version 430 core

uniform sampler2D shadowMap;

in vec4 ShadowCoord;

out vec4 color;

void main(){
		
	/*
	float depth = texture(shadowMap, ShadowCoord.xy).x;
	
	if(depth < (ShadowCoord.z)/ShadowCoord.w){
		color = vec4(0.1f, 0.1f, 0.1f, 1.0f);
	}else{
		color = vec4(0.8f, 0.8f, 0.8f, 1.0f);
	} */
	
	
	color = texture(shadowMap, ShadowCoord.xy);
	
}