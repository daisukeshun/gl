#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "opengl/window.h"
#include "opengl/shaders.h"
#include "utils/u_read.h"


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

static inline void seUniformMatrix4(seShaderProgramCreateInfo program, const GLchar * uniform, const mat4_t value)
{
	GLint location;
	seUseProgram(&program);
	location = glGetUniformLocation(program._id, uniform);
	glUniformMatrix4fv(location, 1, GL_FALSE, m4_array(m4_transpose(value)).mat4);
}

static inline void seUniformVector3(seShaderProgramCreateInfo program, const GLchar * uniform, const vec3_t value)
{
	GLint location;
	seUseProgram(&program);
	location = glGetUniformLocation(program._id, uniform);
	glUniform3fv(location, 1, v3_array(value).vec3);
}

static inline void m4_print(GLfloat * m)
{
	printf("%f\t%f\t%f\t%f\n", m[0], m[1], m[2], m[3]);
	printf("%f\t%f\t%f\t%f\n", m[4], m[5], m[6], m[7]);
	printf("%f\t%f\t%f\t%f\n", m[8], m[9], m[10], m[11]);
	printf("%f\t%f\t%f\t%f\n", m[12], m[13], m[14], m[15]);
}

static inline void v3_print(GLfloat * v)
{
	printf("%f\t%f\t%f\n", v[0], v[1], v[2]);
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

	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	seShaderProgramCreateInfo mainProgram;
	mainProgram.fragmentShaderFilePath	= "./src/shaders/fragment.fs";
	mainProgram.vertexShaderFilePath	= "./src/shaders/vertex.vs";
	seShaderProgramCreate(&mainProgram);

	float vertices[] = {
		-1.0f, -1.0f, -10.0f,
		1.0f, -1.0f, -10.0f,
		0.0f,  1.0f, -10.0f
	};

	GLuint indices[] = {
		0, 1, 2
	};

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
    glBindVertexArray(0);


	mat4_t M = mat4(1.f);
	mat4_t V = mat4(1.f);
	mat4_t P = mat4(1.f);

	M = m4_mul(M, m4_translate(vec3(0, 0, 0.f)));

	V = m4_lookAt(
			vec3(0, 0, 2),
			vec3(0, 0, 1),
			vec3(0, 1, 0));
	m4_print(m4_array(V).mat4);
	printf("\n");
	m4_print((GLfloat*)glm::value_ptr(glm::lookAt(
					glm::vec3(0, 0, 3),
					glm::vec3(0, 0, -1),
					glm::vec3(0, 1, 0)
					)));

	P = m4_mul(P, m4_projection(
				radians(45.f), 
				(GLfloat)mainWindow.width/(GLfloat)mainWindow.height,
				0.1f,
				100.1f));

	seUniformMatrix4(mainProgram, "Projection", P);
	seUniformMatrix4(mainProgram, "View", V);



	vec3_t cameraPosition	= vec3(0, 0, 0);
	vec3_t cameraTarget		= vec3(0, 0, 1);
	vec3_t cameraDirection	= v3_norm(v3_sub(cameraPosition, cameraTarget));
	vec3_t up				= vec3(0, 1, 0);
	vec3_t cameraRight		= v3_norm(v3_cross(up, cameraDirection));
	vec3_t cameraUp			= v3_cross(cameraDirection, cameraRight);

	while(!glfwWindowShouldClose(mainWindow._window)){

		glClearColor(0.05f, 0.05f, 0.15f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//seUniformMatrix4(mainProgram, "View", V);
		seUniformMatrix4(mainProgram, "Model", M);

		seCurrentTime	= glfwGetTime();
		seDeltaTime		= seCurrentTime - seLastFrame;
		seLastFrame		= seCurrentTime;

		//processing input
		
		
		
		
		
		//processing input end

		seUseProgram(&mainProgram);
        glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(mainWindow._window);
		glfwPollEvents();
	}

	seShaderProgramDelete(&mainProgram);
	seWindowDestroy(&mainWindow);
	return 0;
}




