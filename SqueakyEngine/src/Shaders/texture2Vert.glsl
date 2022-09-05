#version 450
#extension GL_ARB_separate_shader_objects : enable

/// Attributes
layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec3 vNormal;

layout(location = 0) uniform mat4 modelMatrix;
layout(location = 1) uniform mat4 viewMatrix;
layout(location = 2) uniform mat4 projectionMatrix;
layout(location = 3) uniform vec3 lightPos;

layout(location = 0) out vec3 vertNormal;
layout(location = 1) out vec3 vertDir;
layout(location = 2) out vec3 vertPos;
layout(location = 3) out vec3 lightDir;
layout(location = 4) out vec3 eyeDir;
layout(location = 5) out vec3 vertex;


uniform  vec3 offset;
uniform sampler3D noiseTexture;
void main() {

     mat4 pureRotationMatrix = transpose(inverse(modelMatrix));
     mat3 normalMatrix = mat3(pureRotationMatrix);
     vertNormal = normalMatrix*vNormal;
     vertNormal = normalize(vertNormal);
     vec4 fvVertex = vec4(-vVertex.x,vVertex.y,vVertex.z,vVertex.w);
   	 vec3 vertPos = vec3(viewMatrix * modelMatrix * fvVertex);
     vertDir = normalize(vertPos);
     vertex = vec3(vVertex);
	vec4 noiseVec = texture(noiseTexture, (vertex * 0.2) + (0.25* offset) );
     lightDir = normalize(lightPos  -vertPos);
     gl_Position =  projectionMatrix * viewMatrix * modelMatrix * (vVertex );
}