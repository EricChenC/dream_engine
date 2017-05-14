#version 430 core

uniform sampler2DShadow shadowMap;

in vec4 ShadowCoord;

out vec4 color;

void main(){		
	
	vec4 LightColor = vec4(1,1,1,1);
	
	float visibility = texture(shadowMap, vec3(ShadowCoord.xy, (ShadowCoord.z)/ShadowCoord.w));

	color = LightColor * visibility;
	
}