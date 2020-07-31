#version 330 core
layout (location = 0) in vec3 aPos;


uniform mat4 MVP;
uniform vec4 color;

out vec4 aColor;
void main()
{
	gl_Position = MVP * vec4(aPos, 1.0); 
	aColor = color;
}
