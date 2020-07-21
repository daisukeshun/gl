#include "scene.h"
#include <GLFW/glfw3.h>

char WindowCreate(WindowCreateInfo * window)
{
	if(!glfwInit()){
		printf("Glfw not initialized\n");
		return -1;
	}

	window->_window = glfwCreateWindow(window->_width, window->_height, window->_name, NULL, NULL);

	if(!window->_window)
	{
		printf("Window is not created\n");
		return -1;
	}

	glfwMakeContextCurrent(window->_window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		  fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));


	return 0;
}


char WindowDestroy(WindowCreateInfo * window)
{
	glfwDestroyWindow(window->_window);
	glfwTerminate();
	return 0;
};
