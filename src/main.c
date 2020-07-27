#include <glm/trigonometric.hpp>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "opengl/scene.h"
#include "opengl/shaders.h"
#include "utils/u_read.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define DEG2RAD 0.0174533

int main()
{
	seWindowCreateInfo mainWindow;
	mainWindow.width = 800;
	mainWindow.height = 600;
	mainWindow.name = "SEngine";
	mainWindow._contextVersionMajor = 3;
	mainWindow._contextVersionMinor = 3;
	seWindowCreate(&mainWindow);


	seShaderProgramCreateInfo mainProgram;
	mainProgram.fragmentShaderFilePath = "./src/shaders/fragment.fs";
	mainProgram.vertexShaderFilePath = "./src/shaders/vertex.vs";
	seShaderProgramCreate(&mainProgram);

	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};

	GLuint indices[] = 
	{
		0, 1, 2
	};

	GLuint vao, vbo, ebo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	glm::mat4 model = glm::mat4(1.0);

	seUniformMatrix(&mainProgram, "model", model);



	while(!glfwWindowShouldClose(mainWindow._window)){
		glClearColor(0.05f, 0.05f, 0.15f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(mainWindow._window);
		glfwPollEvents();
	}

	seWindowDestroy(&mainWindow);
	return 0;
}


