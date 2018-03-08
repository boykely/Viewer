#version 330 core

layout (location = 0) out vec4 glFragColor;

in vec4 gl_Color;

void main()
{
    glFragColor=gl_Color;
}
