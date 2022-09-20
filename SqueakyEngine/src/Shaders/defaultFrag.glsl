#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 fragColor;
layout(location = 0) in vec3 color;
void main() {
    //vec4 fColor = vec4(color,0.0);
   // if(fColor.length ==0){
    fragColor= vec4(1,1,1,1);
   // }
   // else{
   // fragColor = fColor;
}//}