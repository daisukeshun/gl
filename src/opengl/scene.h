#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

typedef struct WindowCreateInfo
{
	
	GLFWwindow * _window;
	GLushort _width, _height;
	const GLchar * _name;

} WindowCreateInfo;

char WindowCreate(WindowCreateInfo * window);
char WindowDestroy(WindowCreateInfo * window);


