#version 430 core
layout (location =0) in vec4 vPosition;
uniform mat4 model_matrix;
uniform mat4 projection_matrix;

void main()
{
	//mat4 m=mat4(1.0);
	//mat4 p=mat4(1.0);
	//gl_Position =p*m*vPosition;
	//gl_Position =vPosition;
	gl_Position=projection_matrix * (model_matrix * vPosition);
	//gl_Position=ftransform();
}