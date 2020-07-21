#version 330 core
in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  

out vec4 FragColor;
void main()
{
	FragColor = vertexColor;
} 
