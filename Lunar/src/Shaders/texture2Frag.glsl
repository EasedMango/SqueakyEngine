#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 vertNormal;
layout(location = 1) in vec3 vertDir;
layout(location = 2) in vec3 vertPos;
layout(location = 3) in vec3 eyeDir;
layout(location = 4) in vec3 lightDir;
layout(location = 5) in vec3 vertex;

layout(location = 0) out vec4 fragColor;

uniform vec3 offset;
uniform sampler3D noiseTexture;
uniform samplerCube skybox;
void main() {
	vec4 ks = vec4(0.2, 0.2, 0.2, 0.0);
	vec4 kd = vec4(0.6, 0.1, 0.6, 0.0); 
	
	vec4 ka = 0.1 * kd;
	vec3 reflectionPhong = normalize(reflect(-lightDir, vertNormal));


	vec3 R = normalize(reflect(vertDir, vertNormal));
		float spec = max(dot(eyeDir, R), 0.0);
    vec3 T = normalize(refract(vertDir, vertNormal,0.99));
	vec4 reflection = texture(skybox,R);
    vec4 refraction = texture(skybox,T);
	vec4 textureColour = texture(skybox,R);
	vec4 color1 = vec4(0.0, 0.0, 0.5,0.0);
	vec4 color2 = vec4(0.0, 0.0, 0.8,0.0);
	vec4 noiseVec = texture(noiseTexture, R+(vertex * 1.25) + offset);

	float intensity = abs(noiseVec[0] - 0.25) +
			     abs(noiseVec[1] - 0.125) + 
			     abs(noiseVec[2] - 0.0625) + 
			     abs(noiseVec[3] - 0.03125);
	intensity = clamp(intensity * 4.0, 0.0, 1.0);
	vec4 mix2 = mix(color1, color2, intensity);
	fragColor =  ka + mix2+ (spec * ks);

}