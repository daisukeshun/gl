#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "opengl/scene.h"
#include "entity/entyty.h"
#include "camera/camera.h"
#include "utils/u_read.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_projection.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtc/type_ptr.hpp>

#define OBJCTS_MAX 100

seCameraCreateInfo mainCamera;

GLfloat se_rand(GLfloat a, GLfloat b) {
    GLfloat random = ((GLfloat) rand()) / (GLfloat) RAND_MAX;
    GLfloat diff = b - a;
    GLfloat r = random * diff;
    return a + r;
}

GLfloat seLastFrame = 0;
GLfloat seDeltaTime = 0;
GLfloat seCurrentTime = 0;

void seInputFunction(seWindowCreateInfo * window, seCameraCreateInfo * camera)
{
	if(glfwGetKey(window->_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window->_window, GL_TRUE);

	if (glfwGetKey(window->_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera->speed = 10.f;

	if (glfwGetKey(window->_window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		camera->speed = 2.5f;

	if (glfwGetKey(window->_window, GLFW_KEY_W) == GLFW_PRESS)
        camera->position += camera->motionSpeed * camera->direction;

    if (glfwGetKey(window->_window, GLFW_KEY_S) == GLFW_PRESS)
        camera->position -= camera->motionSpeed * camera->direction;

    if (glfwGetKey(window->_window, GLFW_KEY_A) == GLFW_PRESS)
        camera->position -= glm::normalize(glm::cross(camera->direction, camera->up)) * camera->mouseSpeed;
    if (glfwGetKey(window->_window, GLFW_KEY_D) == GLFW_PRESS)
        camera->position += glm::normalize(glm::cross(camera->direction, camera->up)) * camera->mouseSpeed;
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

    mainCamera.direction.x = cos(glm::radians(mainCamera.horizontalAngle)) * cos(glm::radians(mainCamera.verticalAngle));
    mainCamera.direction.y = sin(glm::radians(mainCamera.verticalAngle));
    mainCamera.direction.z = sin(glm::radians(mainCamera.horizontalAngle)) * cos(glm::radians(mainCamera.verticalAngle));

	mainCamera.direction = glm::normalize(mainCamera.direction);

	glfwSetCursorPos(window, 400, 300);
}

int main()
{
	srand(time(NULL));

	seWindowCreateInfo mainWindow;
	mainWindow.width	= 800;
	mainWindow.height	= 600;
	mainWindow.name		= "SEngine";
	mainWindow._contextVersionMajor = 3;
	mainWindow._contextVersionMinor = 3;
	seWindowCreate(&mainWindow);

	/*	6 5
	 *	7 4
	 * 2 1
	 * 3 0
	 */

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	seShaderProgramCreateInfo mainProgram;
	mainProgram.fragmentShaderFilePath	= "./src/shaders/fragment.fs";
	mainProgram.vertexShaderFilePath	= "./src/shaders/vertex.vs";
	seShaderProgramCreate(&mainProgram);

	mainCamera.position		= glm::vec3(0, 1, -2);
	mainCamera.direction	= glm::normalize(glm::vec3(0, 0, 1));
	mainCamera.up			= glm::vec3(0, 1, 0);
	mainCamera.mouseSpeed	= 0.05f;
	mainCamera.speed		= 2.5f;
	mainCamera.projection	= glm::perspective(45.f, (GLfloat)mainWindow.width/(GLfloat)mainWindow.height, 0.1f, 100.f);

	seCameraUpdate(&mainCamera);
	seRect * objects		= (seRect*)calloc(OBJCTS_MAX, sizeof(seRect));
	sePlane floor			= sePlaneCreate(&mainProgram);

	floor.rotation	= glm::vec3(glm::radians(90.f), 0, 0);
	floor.color		= glm::vec4(0.3, 0.3, 0.3, 1.f);
	floor.scale		= glm::vec3(100.f);
	floor.position	= glm::vec3(0, 0, 0);

	GLuint i;

	for(i = 0; i < OBJCTS_MAX; i++)
	{
		objects[i] = seRectCreate(&mainProgram);
		objects[i].color = glm::vec4(se_rand(0, 1.f), se_rand(0, 1.f), se_rand(0, 1.f), 1.f);
		objects[i].position.x = se_rand(-100.f, 100.f);
		objects[i].position.y = 0;
		objects[i].position.z = se_rand(-100.f, 100.f);
	}

	glfwSetCursorPosCallback(mainWindow._window, seMouseInputFunction);
	glfwSetInputMode(mainWindow._window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	seUniformMatrix(&mainProgram, "Projection", mainCamera.projection);
	while(!glfwWindowShouldClose(mainWindow._window)){
		glClearColor(0.05f, 0.05f, 0.15f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		seCurrentTime	= glfwGetTime();
		seDeltaTime		= seCurrentTime - seLastFrame;
		seLastFrame		= seCurrentTime;

		seUniformMatrix(&mainProgram, "View", mainCamera.view);
		/*
		objects[0].position = mainCamera.position;

		objects[0].position.x -= 2;
		objects[0].position.y -= 2;
		objects[0].position.z -= 2;

		objects[0].rotation = mainCamera.direction;
		*/

		seUniformVector(&mainProgram, "color", floor.color);
		sePlaneModelUpdate(&floor);
		seUniformMatrix(&mainProgram, "Model", floor.model);
		sePlaneDraw(&floor);

		for(i = 0; i < OBJCTS_MAX; i++)
		{
			seUniformVector(&mainProgram, "color", objects[i].color);
			seRectModelUpdate(&objects[i]);
			seUniformMatrix(&mainProgram, "Model", objects[i].model);
			seRectDraw(&objects[i]);
		}

		mainCamera.motionSpeed = mainCamera.speed * seDeltaTime;
		seCameraUpdate(&mainCamera);
		seInputFunction(&mainWindow, &mainCamera);

		glfwSwapBuffers(mainWindow._window);
		glfwPollEvents();
	}

	sePlaneDelete(&floor);
	for(i = 0; i < OBJCTS_MAX; i++)
	{
		seRectDelete(&objects[i]);
	}

	seShaderProgramDelete(&mainProgram);
	seWindowDestroy(&mainWindow);
	return 0;
}




