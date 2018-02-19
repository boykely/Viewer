#version 330 core

layout (location=0) out vec4 vFragColor;	//fragment shader output


void main()
{
	//set the interpolated colour as the shader output
        vFragColor = vec4(1,1,1,1);
}
