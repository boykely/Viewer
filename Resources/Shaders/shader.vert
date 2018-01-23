#version 330 core
 
layout(location = 0) in vec3 vVertex;	//object space vertex position

void main()
{

   //get the clip space position by multiplying the combined MVP matrix with the object space 
   //vertex position
   gl_Position = vec4(vVertex,1);
}
