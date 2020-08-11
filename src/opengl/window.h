#ifndef WINDOW_H
#define WINDOW_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

typedef struct seWindowCreateInfo
{
	
	GLFWwindow * _window;
	GLushort width, height;
	const GLchar * name;
	GLint _contextVersionMajor;
	GLint _contextVersionMinor;

} seWindowCreateInfo;

void seWindowCreate(seWindowCreateInfo * window);
void seWindowDestroy(seWindowCreateInfo * window);

#endif
