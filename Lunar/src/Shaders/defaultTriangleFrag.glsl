//#version 450
//#extension GL_ARB_separate_shader_objects : enable
//
//layout(location = 0) out vec4 color;
//in vec3 vColor;
//in vec2 uv;
//void main(){
//  color = vec4(vColor,0);//vec4(1.0, 0.0, 0.0, 1.0);
//}
#version 430 core
out vec3 color;
void main(){
  color = vec3(1,0,0);
}