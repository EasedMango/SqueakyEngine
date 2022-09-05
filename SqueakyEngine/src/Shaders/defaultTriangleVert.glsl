//#version 450

//uniform mat4 prjctMtrx;
//layout(location = 0) in vec4 vVertex;
//layout(location = 1) in vec3 vNormal;
//layout(location = 2) in vec2 uvCoord;
//uniform mat4 MVP;
//out vec3 vColor;
//
//void main(){
//	vColor = vec3(vVertex);
//	gl_Position = vVertex;
//}
#version 430 core

layout(location = 0) in vec3 vertexPosition_modelspace;


void main()
{
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1.0;

}
