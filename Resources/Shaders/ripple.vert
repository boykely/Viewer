#version 330 core

layout (location=0) in vec3 vVertex;
layout(location=1) in vec3 vColor;

out vec4 gl_Color;

uniform mat4 MVP;

void main()
{
    gl_Position=MVP*vec4(vVertex.x,vVertex.y,vVertex.z,1);
    gl_Color=vec4(vColor,1);
}
