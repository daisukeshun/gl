#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

typedef struct WindowCreateInfo
{
	
	GLFWwindow * _window;
	unsigned short _width, _height;
	const char * _name;

} WindowCreateInfo;

char WindowCreate(WindowCreateInfo * window);
char WindowDestroy(WindowCreateInfo * window);


