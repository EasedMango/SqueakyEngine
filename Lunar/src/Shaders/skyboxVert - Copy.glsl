#version 450
#extension GL_ARB_separate_shader_objects : enable

/// Attributes
layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec3 uvCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


layout(location = 0) out vec3 texCoord;



void main() {

    texCoord = vec3(-vVertex.x,vVertex.y,vVertex.z);
    gl_Position = projectionMatrix * viewMatrix*modelMatrix*vVertex;
}