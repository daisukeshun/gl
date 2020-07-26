#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include "opengl/scene.h"
#include "opengl/shaders.h"
#include "utils/u_read.h"

int main()
{

	WindowCreateInfo mainWindow;
	mainWindow._width = 800;
	mainWindow._height = 600;
	mainWindow._name = "SEngine";
	WindowCreate(&mainWindow);

	ShaderProgramCreateInfo mainProgram;
	mainProgram.vertexShaderSource = "./src/shaders/vertex.vs";
	mainProgram.fragmentShaderSource = "./src/shaders/fragment.fs.vs";
	ShaderProgramCreate(&mainProgram);

	while(!glfwWindowShouldClose(mainWindow._window)){
		glClearColor(0.05f, 0.05f, 0.05f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(0);
		glfwSwapBuffers(mainWindow._window);
		glfwPollEvents();
	}

	WindowDestroy(&mainWindow);
	return 0;
}


