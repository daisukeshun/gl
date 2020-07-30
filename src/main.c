#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "opengl/scene.h"
#include "opengl/shaders.h"
#include "camera/camera.h"
#include "utils/u_read.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/type_ptr.hpp>

#define DEG2RAD 0.0174533f
#define OBJCTS_MAX 10

seCameraCreateInfo mainCamera;
glm::mat4 mvp;

GLfloat lastFrame = 0;
GLfloat deltaTime = 0;
void seInputFunction(seWindowCreateInfo * window)
{

	if (glfwGetKey(window->_window, GLFW_KEY_W) == GLFW_PRESS)
        mainCamera.position += mainCamera.speed * mainCamera.direction;
    if (glfwGetKey(window->_window, GLFW_KEY_S) == GLFW_PRESS)
        mainCamera.position -= mainCamera.speed * mainCamera.direction;
    if (glfwGetKey(window->_window, GLFW_KEY_A) == GLFW_PRESS)
        mainCamera.position -= glm::normalize(glm::cross(mainCamera.direction, mainCamera.up)) * mainCamera.mouseSpeed;
    if (glfwGetKey(window->_window, GLFW_KEY_D) == GLFW_PRESS)
        mainCamera.position += glm::normalize(glm::cross(mainCamera.direction, mainCamera.up)) * mainCamera.mouseSpeed;
}

void seMouseInputFunction(GLFWwindow * window, GLdouble x, GLdouble y)
{

	GLfloat offsetx, offsety;
	GLfloat centerx, centery;
	centerx = 400;
	centery = 300;
	offsetx = x - centerx;
	offsety = y - centery;


	float sensitivity = 0.1f;
    offsetx *= sensitivity;
    offsety *= sensitivity;

	mainCamera.verticalAngle -= offsety;
	mainCamera.horizontalAngle += offsetx;

	if(mainCamera.verticalAngle > 89.0f)
	{
        mainCamera.verticalAngle = 89.0f;
	}
    if(mainCamera.verticalAngle < -89.0f)
	{
        mainCamera.verticalAngle = -89.0f;
	}

	glm::vec3 direction;
    direction.x = cos(glm::radians(mainCamera.horizontalAngle)) * cos(glm::radians(mainCamera.verticalAngle));
    direction.y = sin(glm::radians(mainCamera.verticalAngle));
    direction.z = sin(glm::radians(mainCamera.horizontalAngle)) * cos(glm::radians(mainCamera.verticalAngle));

	mainCamera.direction = glm::normalize(direction);

	glfwSetCursorPos(window, 400, 300);
}

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
	mvp = mainCamera.matrix * model;
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

	mainCamera.position = glm::vec3(0, 0, 0);
	mainCamera.direction = glm::vec3(0, 0, -1);
	mainCamera.up = glm::vec3(0, 1, 0);
	mainCamera.mouseSpeed = 0.05f;
	mainCamera.speed = 2.5f;
	mainCamera.projection = glm::perspective(45.f, 
			(GLfloat)mainWindow.width/(GLfloat)mainWindow.height, 
			0.1f, 100.f);

	seCameraUpdate(&mainCamera);
	seCameraMoveTo(&mainCamera, 0, 0, 1);
	seRect * objects = (seRect*)calloc(OBJCTS_MAX, sizeof(seRect));

	GLuint i;

	GLfloat currentTime = 0;
	for(i = 0; i < OBJCTS_MAX; i++)
	{
		objects[i] = seRectCreate(&mainProgram);
	}

	glfwSetCursorPosCallback(mainWindow._window, seMouseInputFunction);

	glfwSetInputMode(mainWindow._window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	while(!glfwWindowShouldClose(mainWindow._window)){
		glClearColor(0.05f, 0.05f, 0.15f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrame;
		lastFrame = currentTime;

		mainCamera.speed = 2.5f * deltaTime;
		seInputFunction(&mainWindow);
		seCameraUpdate(&mainCamera);

		for(i = 0; i < OBJCTS_MAX; i++)
		{
			seRectDraw(&objects[i]);
			seRectModelUpdate(&objects[i]);
			seUpdateMVP(&mainProgram, objects[i].model);
		}

		glfwSwapBuffers(mainWindow._window);
		glfwPollEvents();
	}

	for(i = 0; i < OBJCTS_MAX; i++)
	{
		seDeleteRect(&objects[i]);
	}

	seWindowDestroy(&mainWindow);
	return 0;
}


