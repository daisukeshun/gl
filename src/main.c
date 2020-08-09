#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "opengl/scene.h"
#include "camera/camera.h"
#include "entity/entyty.h"
#include "utils/u_read.h"
#include "control/control.h"

#include <GLFW/glfw3.h>

GLfloat gravityForce = 1.0;

#define OBJCTS_MAX 100

GLfloat se_rand(GLfloat a, GLfloat b) {
    GLfloat random = ((GLfloat) rand()) / (GLfloat) RAND_MAX;
    GLfloat diff = b - a;
    GLfloat r = random * diff;
    return a + r;
}

GLfloat seLastFrame = 0;
GLfloat seDeltaTime = 0;
GLfloat seCurrentTime = 0;

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

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	seShaderProgramCreateInfo mainProgram;
	mainProgram.fragmentShaderFilePath	= "./src/shaders/fragment.fs";
	mainProgram.vertexShaderFilePath	= "./src/shaders/vertex.vs";
	seShaderProgramCreate(&mainProgram);

	seCameraCreateInfo mainCamera;
	mainCamera.mouseSpeed	= 0.05f;
	mainCamera.speed		= 2.5f;
	mainCamera.cursor		= 0;
	mainCamera.fov			= 45.f;
	mainCamera.aspect		= (GLfloat)mainWindow.width/(GLfloat)mainWindow.height;
	mainCamera.znear		= 0.1f;
	mainCamera.zfar			= 100.1f;
	mainCamera.position		= vec3(0.f, 0.f, 0.f);
	mainCamera.direction	= vec3(0.f, 1.f, 0.f);
	mainCamera.up			= vec3(0.f, 0.f, 1.f);
	svec3(&mainCamera.position, 0, 0, 0);

	printf("%f %f %f\n", mainCamera.position.x, mainCamera.position.y, mainCamera.position.z);

	while(!glfwWindowShouldClose(mainWindow._window)){
		seMouseInputFunction(&mainWindow, &mainCamera);
		seInputFunction(&mainWindow, &mainCamera);

		glClearColor(0.05f, 0.05f, 0.15f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		seCurrentTime	= glfwGetTime();
		seDeltaTime		= seCurrentTime - seLastFrame;
		seLastFrame		= seCurrentTime;


		printf("%f %f %f\n", mainCamera.direction.x, mainCamera.direction.y, mainCamera.direction.z);
		glfwSwapBuffers(mainWindow._window);
		glfwPollEvents();
	}

	seShaderProgramDelete(&mainProgram);
	seWindowDestroy(&mainWindow);
	return 0;
}




