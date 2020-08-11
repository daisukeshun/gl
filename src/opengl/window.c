#include "window.h"
#include <GLFW/glfw3.h>

char seWindowCreate(seWindowCreateInfo * window)
{
	if(!glfwInit()){
		printf("Glfw not initialized\n");
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, window->_contextVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, window->_contextVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window->_window = glfwCreateWindow(window->width, window->height, window->name, NULL, NULL);
	if(!window->_window)
	{
		printf("Window is not created\n");
		return -1;
	}
	glfwMakeContextCurrent(window->_window);

	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		  fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
	glViewport(0, 0, window->width, window->height);
	glEnable(GL_DEPTH_TEST );
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	return 0;
}


char seWindowDestroy(seWindowCreateInfo * window)
{
	glfwDestroyWindow(window->_window);
	glfwTerminate();
	return 0;
};
