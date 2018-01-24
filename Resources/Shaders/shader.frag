#version 330 core

in vec4 glColor;

out vec4 vFragColor;	//fragment shader output


void main()
{
	//set the interpolated colour as the shader output
        vFragColor = glColor;
}
