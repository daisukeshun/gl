#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include "opengl/scene.h"
#include "opengl/shaders.h"
#include "utils/u_read.h"
#include "utils/u_pointers.h"
#include "types/m_types.h"
#include "math/matrix.h"

int main(int argc, char ** argv)
{

	WindowCreateInfo mainWindow;
	mainWindow._width = 800;
	mainWindow._height = 600;
	mainWindow._name = "SEngine";
	WindowCreate(&mainWindow);

	ShaderGroup mainGroup;

	mainGroup = setShaderGroup("./src/shaders/vertex.vs", "./src/shaders/fragment.fs", 2);

	mainGroup.member[0] = setObject(12, 4, 0);
	setName(&mainGroup.member[0].name, "Something");

	mainGroup.member[0].vrts[0] = -1.0;
	mainGroup.member[0].vrts[1] = -1.0;
	mainGroup.member[0].vrts[2] = 0.0;

	mainGroup.member[0].vrts[3] = -1.0;
	mainGroup.member[0].vrts[4] = -1.0;
	mainGroup.member[0].vrts[5] = 100.0;

	mainGroup.member[0].vrts[6] = 1.0;
	mainGroup.member[0].vrts[7] = -1.0;
	mainGroup.member[0].vrts[8] = 100.0;

	mainGroup.member[0].vrts[9] = 1.0;
	mainGroup.member[0].vrts[10] = -1.0;
	mainGroup.member[0].vrts[11] = 0.0;

	mainGroup.member[1] = setObject(12, 4, 0);
	setName(&mainGroup.member[1].name, "Rectangle");

	mainGroup.member[1].vrts[0] = -1.0;
	mainGroup.member[1].vrts[1] = -1.0;
	mainGroup.member[1].vrts[2] = 3.0;

	mainGroup.member[1].vrts[3] = -1.0;
	mainGroup.member[1].vrts[4] = 1.0;
	mainGroup.member[1].vrts[5] = 3.0;

	mainGroup.member[1].vrts[6] = 1.0;
	mainGroup.member[1].vrts[7] = 1.0;
	mainGroup.member[1].vrts[8] = 3.0;

	mainGroup.member[1].vrts[9] = 1.0;
	mainGroup.member[1].vrts[10] = -1.0;
	mainGroup.member[1].vrts[11] = 3.0;

	glUseProgram(mainGroup.programID);


	GLfloat * p = setPerspective(45.0f, (float)mainWindow._width/(float)mainWindow._height, 0.1f, 100.0f);

	mainGroup.member[0].rotation = setRotation(0.0, 0.0f, 0.f);
	mainGroup.member[0].position = setTranslate(0.0, 0.5f, -5.f);

	mainGroup.member[1].rotation = setRotation(0.0, 30.0f, 0.f);
	mainGroup.member[1].position = setTranslate(0.0, 0.5f, -10.f);


	GLsizei i = 0;

	setUniformMatrix4f(mainGroup.programID, "projection", p);
	while(!glfwWindowShouldClose(mainWindow._window)){
		glClearColor(0.05f, 0.05f, 0.05f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		for(i = 0; i < mainGroup.memberCount; i++)
			loadObject(&mainGroup.member[i]);

		for(i = 0; i < mainGroup.memberCount; i++)
		{
			setUniformMatrix4f(mainGroup.programID, "model", mainGroup.member[i].rotation);
			setUniformMatrix4f(mainGroup.programID, "view", mainGroup.member[i].position);
			glBindVertexArray(mainGroup.member[i].vao);
			glDrawArrays(GL_QUADS, 0, 4);
		}

		glBindVertexArray(0);
		glfwSwapBuffers(mainWindow._window);
		glfwPollEvents();
	}

	deleteShaderGroup(&mainGroup);

	printf("%d", mainGroup.programID);

	WindowDestroy(&mainWindow);
	return 0;
}


