#version 330 core

//object space vertex position
layout(location = 0) in vec3 vVertex;

uniform mat4 MVP;

void main()
{
   //vertex position
    gl_Position =MVP* vec4(vVertex,1);
}
