#version 330 core

//object space vertex position
layout(location = 0) in vec3 vVertex;

void main()
{
   //vertex position
   gl_Position = vec4(vVertex,1);
}
