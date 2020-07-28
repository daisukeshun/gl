#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "opengl/scene.h"
#include "opengl/shaders.h"
#include "utils/u_read.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/type_ptr.hpp>

#define DEG2RAD 0.0174533f

glm::mat4 view;
glm::mat4 projection;
glm::mat4 mvp;
typedef struct seRect
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 model;

	GLfloat * vertexData;
	GLuint * elementData;
	GLuint vertexDataSize;
	GLuint elemetDataSize;

	GLuint vao, vbo, ebo;
	GLuint shaderProgramId;
} seRect;

seRect seRectCreate(seShaderProgramCreateInfo * program)
{
	seRect rect;

	rect.position = glm::vec3(0);
	rect.rotation = glm::vec3(0);
	rect.scale = glm::vec3(1.f);

	rect.model = glm::mat4(1.f);
	rect.model = glm::translate(rect.model, rect.position);
	rect.model = glm::rotate(rect.model, rect.rotation.z * DEG2RAD, glm::vec3(0, 0, 1));
	rect.model = glm::rotate(rect.model, rect.rotation.y * DEG2RAD, glm::vec3(0, 1, 0));
	rect.model = glm::rotate(rect.model, rect.rotation.x * DEG2RAD, glm::vec3(1, 0, 0));
	rect.model = glm::scale(rect.model, rect.scale);


	rect.elemetDataSize = 6 * sizeof(GLuint);
	rect.vertexDataSize = 12 * sizeof(GLfloat);

	rect.elementData = (GLuint*)malloc(rect.elemetDataSize);
	rect.vertexData = (GLfloat*)malloc(rect.vertexDataSize);

	rect.vertexData[0] = -0.5;
	rect.vertexData[1] = -0.5;
	rect.vertexData[2] = 0;

	rect.vertexData[3] = -0.5;
	rect.vertexData[4] = 0.5;
	rect.vertexData[5] = 0;

	rect.vertexData[6] = 0.5;
	rect.vertexData[7] = 0.5;
	rect.vertexData[8] = 0;

	rect.vertexData[9] = 0.5;
	rect.vertexData[10] = -0.5;
	rect.vertexData[11] = 0;

	rect.elementData[0] = 0;
	rect.elementData[1] = 1;
	rect.elementData[2] = 2;
	rect.elementData[3] = 2;
	rect.elementData[4] = 3;
	rect.elementData[5] = 0;

	glGenVertexArrays(1, &rect.vao);
	glBindVertexArray(rect.vao);

	glGenBuffers(1, &rect.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, rect.vbo);
	glBufferData(GL_ARRAY_BUFFER, rect.vertexDataSize, rect.vertexData, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &rect.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rect.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, rect.elemetDataSize, rect.elementData, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	rect.shaderProgramId = program->_id;

	glBindVertexArray(0);
	return rect;
}

void seRectModelUpdate(seRect * rect)
{
	rect->model = glm::mat4(1.f);
	rect->model = glm::translate(rect->model, rect->position);
	rect->model = glm::rotate(rect->model, rect->rotation.z, glm::vec3(0, 0, 1));
	rect->model = glm::rotate(rect->model, rect->rotation.y, glm::vec3(0, 1, 0));
	rect->model = glm::rotate(rect->model, rect->rotation.x, glm::vec3(1, 0, 0));
	rect->model = glm::scale(rect->model, rect->scale);
}

void seRectDraw(seRect * rect)
{
	glBindVertexArray(rect->vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

char seDeleteRect(seRect * rect)
{
	free(rect->elementData);
	free(rect->vertexData);
	rect->elemetDataSize = 0;
	rect->vertexDataSize = 0;
	rect->shaderProgramId = 0;
	glDeleteBuffers(1, &rect->ebo);
	glDeleteBuffers(1, &rect->vbo);
	glDeleteVertexArrays(1, &rect->vao);
	return 0;
};

void seUpdateMVP(seShaderProgramCreateInfo * program, glm::mat4 model)
{
	mvp = projection * view * model;
	seUniformMatrix(program, "MVP", mvp);
}

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

	view = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	projection = glm::perspective(45.f, (GLfloat)mainWindow.width/(GLfloat)mainWindow.height, 0.1f, 100.f);

	seRect r0 = seRectCreate(&mainProgram);
	seRect r1 = seRectCreate(&mainProgram);

	r1.position = glm::vec3(1.5, 0, 0);
	r1.rotation = glm::vec3(0, 0, 20);
	r1.scale = glm::vec3(0.5, 0.1, 1);
	r0.position = glm::vec3(-1.5, 0, -2);

	while(!glfwWindowShouldClose(mainWindow._window)){
		glClearColor(0.05f, 0.05f, 0.15f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		seRectDraw(&r0);
		seRectModelUpdate(&r0);
		seUpdateMVP(&mainProgram, r0.model);

		seRectDraw(&r1);
		seRectModelUpdate(&r1);
		seUpdateMVP(&mainProgram, r1.model);

		glfwSwapBuffers(mainWindow._window);
		glfwPollEvents();
	}

	seDeleteRect(&r0);
	seDeleteRect(&r1);
	seWindowDestroy(&mainWindow);
	return 0;
}


