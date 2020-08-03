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

#include <GLFW/glfw3.h>

#include "physics/collision.h"

GLfloat gravityForce = 0.1;

#define OBJCTS_MAX 1

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

GLchar seCollisionRectConstructByVertexArrayData(seCollisionRectCreateInfo * r, seRect * object)
{
	glm::vec4 mintmp = glm::vec4(object->vertexData[0], object->vertexData[1], object->vertexData[2], 1.f);
	glm::vec4 maxtmp = glm::vec4(object->vertexData[0], object->vertexData[1], object->vertexData[2], 1.f);

	for(GLuint j = 0; j + 2 < object->vertexDataSize / sizeof(GLfloat); j+=3)
	{
		mintmp.x = glm::min(object->vertexData[j + 0], mintmp.x);
		mintmp.y = glm::min(object->vertexData[j + 1], mintmp.y);
		mintmp.z = glm::min(object->vertexData[j + 2], mintmp.z);

		maxtmp.x = glm::max(object->vertexData[j + 0], maxtmp.x);
		maxtmp.y = glm::max(object->vertexData[j + 1], maxtmp.y);
		maxtmp.z = glm::max(object->vertexData[j + 2], maxtmp.z);
	}
	seRectModelUpdate(object);
	mintmp = object->model * mintmp;
	maxtmp = object->model * maxtmp;

	r->x0 = mintmp.x;
	r->y0 = mintmp.y;
	r->z0 = mintmp.z;

	r->x1 = maxtmp.x;
	r->y1 = maxtmp.y;
	r->z1 = maxtmp.z;

	/*
	printf("%f %f %f\n", r->x0, r->y0, r->z0);
	printf("%f %f %f\n", r->x1, r->y1, r->z1);
	 */

	return 0;
}
GLchar seCollisionRectConstructByVertexArrayData(seCollisionRectCreateInfo * r, sePlane * object)
{
	glm::vec4 mintmp = glm::vec4(object->vertexData[0], object->vertexData[1], object->vertexData[2], 1.f);
	glm::vec4 maxtmp = glm::vec4(object->vertexData[0], object->vertexData[1], object->vertexData[2], 1.f);

	for(GLuint j = 0; j + 2 < object->vertexDataSize / sizeof(GLfloat); j+=3)
	{
		mintmp.x = glm::min(object->vertexData[j + 0], mintmp.x);
		mintmp.y = glm::min(object->vertexData[j + 1], mintmp.y);
		mintmp.z = glm::min(object->vertexData[j + 2], mintmp.z);

		maxtmp.x = glm::max(object->vertexData[j + 0], maxtmp.x);
		maxtmp.y = glm::max(object->vertexData[j + 1], maxtmp.y);
		maxtmp.z = glm::max(object->vertexData[j + 2], maxtmp.z);
	}
	sePlaneModelUpdate(object);
	mintmp = object->model * mintmp;
	maxtmp = object->model * maxtmp;

	r->x0 = mintmp.x;
	r->y0 = mintmp.y;
	r->z0 = mintmp.z;

	r->x1 = maxtmp.x;
	r->y1 = maxtmp.y;
	r->z1 = maxtmp.z;
	return 0;
}

void seInputFunction(seWindowCreateInfo * window, seCameraCreateInfo * camera)
{
	if(glfwGetKey(window->_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{	
		glfwSetInputMode(window->_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		camera->cursor = 1;
	}
	if(glfwGetKey(window->_window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
	{
		glfwSetInputMode(window->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		camera->cursor = 2;
	}

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
	GLint centerx, centery;
	GLfloat offsetx, offsety;
	GLfloat sensitivity = 0.1f;
	glfwGetWindowSize(window, &centerx, &centery);

	centerx /= 2;
	centery /= 2;

	if(mainCamera.cursor == 0)
	{
		offsetx = x - (GLfloat)centerx;
		offsety = y - (GLfloat)centery;

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
	}
	if(mainCamera.cursor == 2)
	{
		mainCamera.cursor = 0;
	}

	if(!mainCamera.cursor)
	{
		glfwSetCursorPos(window, centerx, centery);
	}
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
	seRect * objects					= (seRect*)calloc(OBJCTS_MAX, sizeof(seRect));
	sePlane floor						= sePlaneCreate(&mainProgram);
	seCollisionRectCreateInfo * rects	= (seCollisionRectCreateInfo *)calloc(OBJCTS_MAX, sizeof(seCollisionRectCreateInfo));

	floor.rotation	= glm::vec3(glm::radians(90.f), 0, 0);
	floor.color		= glm::vec4(0.3, 0.3, 0.3, 1.f);
	floor.scale		= glm::vec3(10.f);
	floor.position	= glm::vec3(1, -10, 0);

	sePlaneModelUpdate(&floor);
	seCollisionRectCreateInfo floorCollider;

	floorCollider.state = 0;
	rects[0].state = 0;

	GLuint i;

	for(i = 0; i < OBJCTS_MAX; i++)
	{
		objects[i] = seRectCreate(&mainProgram);
		objects[i].color = glm::vec4(se_rand(0, 1.f), se_rand(0, 1.f), se_rand(0, 1.f), 1.f);
		//objects[i].position.x = se_rand(-100.f, 100.f);
		//objects[i].position.y = 0;
		//objects[i].position.z = se_rand(-100.f, 100.f);
	}

	glfwSetCursorPosCallback(mainWindow._window, seMouseInputFunction);
	seUniformMatrix(&mainProgram, "Projection", mainCamera.projection);
	while(!glfwWindowShouldClose(mainWindow._window)){
		glClearColor(0.05f, 0.05f, 0.15f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		seCurrentTime	= glfwGetTime();
		seDeltaTime		= seCurrentTime - seLastFrame;
		seLastFrame		= seCurrentTime;

		seUniformMatrix(&mainProgram, "View", mainCamera.view);
		//objects[0].position = mainCamera.position;

		/*
		objects[0].position.x -= 2;
		objects[0].position.y -= 2;
		objects[0].position.z -= 2;
		objects[0].rotation = mainCamera.direction;
		*/

		seUniformVector(&mainProgram, "color", floor.color);
		sePlaneModelUpdate(&floor);
		seUniformMatrix(&mainProgram, "Model", floor.model);
		sePlaneDraw(&floor);

		seCollisionRectConstructByVertexArrayData(&floorCollider, &floor);

		for(i = 0; i < OBJCTS_MAX; i++)
		{
			seCollisionRectConstructByVertexArrayData(&rects[i], &objects[i]);

			seRRColisionDetect(&rects[i], &floorCollider);

			if(!rects[i].state)
			{
				objects[i].position.y -= gravityForce;
			}

			seUniformVector(&mainProgram, "color", objects[i].color);
			seRectModelUpdate(&objects[i]);
			seUniformMatrix(&mainProgram, "Model", objects[i].model);
			seRectDraw(&objects[i]);
		}

		//printf("%d %d\n", floorCollider.state, rects[0].state);

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




