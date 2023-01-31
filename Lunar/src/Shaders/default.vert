#version 450
#extension GL_ARB_separate_shader_objects : enable

/// Attributes
layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 uvCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


layout(location = 0) out vec2 texCoord;
layout(location = 1) out vec3 vertNormal;
layout(location = 2) out vec3 lightDir;
layout(location = 3) out vec3 eyeDir;


void main() {


    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vVertex;//*vec4(1,1,1,1);
}