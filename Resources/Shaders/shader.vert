#version 330 core

//object space vertex position
layout(location = 0) in vec3 vVertex;
layout(location=1) in vec3 vColor;

out vec4 glColor;

uniform mat4 MVP;

void main()
{
   //vertex position
    glColor=vec4(vColor,1);
    gl_Position = vec4(vVertex,1);
}
