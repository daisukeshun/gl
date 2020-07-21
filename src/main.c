#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include "opengl/scene.h"
#include "opengl/shaders.h"
#include "utils/u_read.h"
#include "utils/u_pointers.h"
#include "utils/u_array.h"
#include "math/matrix.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(int argc, char ** argv)
{

	WindowCreateInfo mainWindow;
	mainWindow._width = 800;
	mainWindow._height = 600;
	mainWindow._name = "SEngine";
	WindowCreate(&mainWindow);

	float vertices[] = {
	 -0.5f, -0.5f, 0.0f,
     -0.5f, 0.5f, 0.0f,
     0.5f, 0.5f, 0.0f,
	 0.5, -0.5f, 0.0f
	};


	GLuint vs, fs, program;
	GLuint vao, vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), (const void *)vertices , GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(0);

	GLchar * text = u_read("./src/shaders/vertex.vs");
	ShaderCreate(&vs, GL_VERTEX_SHADER, text);
	del((void*)text);

	text = u_read("./src/shaders/fragment.fs");
	ShaderCreate(&fs, GL_FRAGMENT_SHADER, text);
	del((void*)text);

	ShaderProgramCreate(&program, &vs, &fs);

	glUseProgram(program);

	printf("%f\n", (float)mainWindow._width);
	printf("%f\n", (float)mainWindow._height);

	GLfloat * p = setPerspective(45.0f, (float)mainWindow._width/(float)mainWindow._height, 0.1f, 100.0f);
	GLfloat * v = setTranslate(0.0, 0.0, -1.0f);
	

	matrix_print(p);

	GLuint location = glGetUniformLocation(program, "projection");
	glUniformMatrix4fv(location, 1, GL_FALSE, p);

	location = glGetUniformLocation(program, "view");
	glUniformMatrix4fv(location, 1, GL_FALSE, v);

	while(!glfwWindowShouldClose(mainWindow._window)){
		glClearColor(0.05f, 0.05f, 0.05f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glBindVertexArray(vao);
		glDrawArrays(GL_QUADS, 0, 4);
		glBindVertexArray(0);

		glfwSwapBuffers(mainWindow._window);
		glfwPollEvents();
	}

	glDeleteProgram(program);
	WindowDestroy(&mainWindow);

	return 0;
}


