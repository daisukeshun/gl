#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "opengl/window.h"
#include "opengl/shaders.h"
#include "utils/u_read.h"

#include <GLFW/glfw3.h>

GLfloat gravityForce = 1.0;

static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

static inline void seUniformMatrix4(seShaderProgramCreateInfo program, const GLchar * uniform, const mat4_t value);

typedef struct seObjectCreateInfo
{
	GLchar * modelFile;
	GLuint vao, vbo, ebo;

	GLint elementsCount, verticesCount;
	seShaderProgramCreateInfo program;

	mat4_t model;

	vec3_t position,
		   rotation,
		   scale,
		   axis;

} seObjectCreateInfo;

static inline void seObjectCreate(seObjectCreateInfo * object)
{
	glGenVertexArrays(1, &object->vao);

	glGenBuffers(1, &object->vbo);
	glGenBuffers(1, &object->ebo);

}

static inline void seObjectData(seObjectCreateInfo * object, GLfloat * vertices, GLint verticesDataSize, GLuint * indices, GLint indicesDataSize)
{
	object->elementsCount = indicesDataSize/sizeof(GLuint);
	object->verticesCount = verticesDataSize/sizeof(GLfloat);
    glBindVertexArray(object->vao);
		glBindBuffer(GL_ARRAY_BUFFER, object->vbo);
		glBufferData(GL_ARRAY_BUFFER, verticesDataSize , vertices, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesDataSize, indices, GL_DYNAMIC_DRAW);

		glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

static inline void seObjectDrawElements(seObjectCreateInfo * object)
{
	//model matrix update
	object->model = mat4(1.f);
	object->model = m4_mul(object->model, m4_translate(object->position));
	object->model = m4_mul(object->model, m4_rotate(object->rotation.x, vec3(1, 0, 0)));
	object->model = m4_mul(object->model, m4_rotate(object->rotation.y, vec3(0, 1, 0)));
	object->model = m4_mul(object->model, m4_rotate(object->rotation.z, vec3(0, 0, 1)));
	object->model = m4_mul(object->model, m4_scale(object->scale));


	seShaderProgramUse(&object->program);
	seUniformMatrix4(object->program, "Model", object->model);
    glBindVertexArray(object->vao);
	glDrawElements(GL_TRIANGLES, object->elementsCount, GL_UNSIGNED_INT, 0);

}

static inline void seObjectDrawArrays(seObjectCreateInfo * object)
{
	//model matrix update
	object->model = mat4(1.f);
	object->model = m4_mul(object->model, m4_translate(object->position));
	object->model = m4_mul(object->model, m4_rotate(object->rotation.x, vec3(1, 0, 0)));
	object->model = m4_mul(object->model, m4_rotate(object->rotation.y, vec3(0, 1, 0)));
	object->model = m4_mul(object->model, m4_rotate(object->rotation.z, vec3(0, 0, 1)));
	object->model = m4_mul(object->model, m4_scale(object->scale));


	seShaderProgramUse(&object->program);
	seUniformMatrix4(object->program, "Model", object->model);
    glBindVertexArray(object->vao);
	glDrawArrays(GL_TRIANGLES, 0, object->verticesCount);

}

static inline void seObjectDelete(seObjectCreateInfo * object)
{
	glDeleteBuffers(1, &object->vbo);
	glDeleteBuffers(1, &object->ebo);
	glDeleteVertexArrays(1, &object->vao);
	object->vao = object->vbo = object->ebo = 0;
}



typedef struct seCameraCreateInfo
{
	vec3_t yaw_pitch_roll;

	vec3_t position;
	vec3_t target;
	vec3_t up;

	mat4_t matrix;
} seCameraCreateInfo;



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
	seShaderProgramUse(&program);
	location = glGetUniformLocation(program._id, uniform);
	glUniformMatrix4fv(location, 1, GL_FALSE, m4_array(m4_transpose(value)).mat4);
}

static inline void seUniformVector3(seShaderProgramCreateInfo program, const GLchar * uniform, const vec3_t value)
{
	GLint location;
	seShaderProgramUse(&program);
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

	//glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	seShaderProgramCreateInfo mainProgram;
		mainProgram.fragmentShaderFilePath	= "./src/shaders/fragment.fs";
		mainProgram.vertexShaderFilePath	= "./src/shaders/vertex.vs";
	seShaderProgramCreate(&mainProgram);


	GLfloat vertices[] = {
		-1.0f, -1.0f, -10.0f,
		1.0f, -1.0f, -10.0f,
		1.0f,  1.0f, -10.0f,
		-1.0f,  1.0f, -10.0f
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	seObjectCreateInfo floor;
		floor.position		= vec3(0, 0, 0);
		floor.rotation		= vec3(0, 0, 0);
		floor.scale			= vec3(1, 1, 1);
		floor.elementsCount	= sizeof(indices)/sizeof(GLuint);
		floor.model			= mat4(1.0);
		floor.program		= mainProgram;
	seObjectCreate(&floor);
	seObjectData(&floor, (GLfloat*)g_vertex_buffer_data, sizeof(g_vertex_buffer_data), indices, sizeof(indices));

	vec3_t cameraPosition	= vec3(0, 0, 0);
	vec3_t cameraFront		= vec3(0, 0, 1);
	vec3_t cameraUp			= vec3(0, 1, 0);

	mat4_t P = mat4(1.f);
	P = m4_mul(P, m4_projection(
				radians(45.f), 
				(GLfloat)mainWindow.width/(GLfloat)mainWindow.height,
				0.1f,
				100.1f));

	mat4_t V = mat4(1.f);
	V = m4_lookAt(cameraPosition, v3_add(cameraPosition, cameraFront), cameraUp);

	GLdouble xpos, ypos;
	GLfloat speed = 0.3f;
	GLfloat velocity = 1.f;
	GLfloat mouseSpeed = 0.05f;
	GLfloat lastX = mainWindow.width/2, lastY = mainWindow.height/2;
	GLfloat yaw = 0, pitch = 0, roll = 0;

	GLfloat velocityInputTime	= 0;
	GLfloat velocityInputDelta	= 0;
	GLboolean 
			w_pressed = GL_FALSE,
			a_pressed = GL_FALSE,
			s_pressed = GL_FALSE,
			d_pressed = GL_FALSE;

	seUniformMatrix4(mainProgram, "Projection", P);
	while(!glfwWindowShouldClose(mainWindow._window)){

		glClearColor(0.05f, 0.05f, 0.15f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		seUniformMatrix4(mainProgram, "View", V);

		seCurrentTime	= glfwGetTime();
		seDeltaTime		= seCurrentTime - seLastFrame;
		seLastFrame		= seCurrentTime;

		//processing input
		glfwSetInputMode(mainWindow._window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwGetCursorPos(mainWindow._window, &xpos, &ypos);
		
		//////////////////////////////////////////////////////////////w
		if (glfwGetKey(mainWindow._window, GLFW_KEY_W) == GLFW_PRESS)
		{
			if(!w_pressed)
			{
				velocityInputTime = seCurrentTime;
				w_pressed = GL_TRUE;
			}
			cameraPosition = v3_add(cameraPosition, v3_muls(cameraFront, speed));
		}
		if (glfwGetKey(mainWindow._window, GLFW_KEY_W) == GLFW_RELEASE)
		{
			w_pressed = GL_FALSE;
		}
		//////////////////////////////////////////////////////////////s
		if (glfwGetKey(mainWindow._window, GLFW_KEY_S) == GLFW_PRESS)
		{
			if(!s_pressed)
			{
				velocityInputTime = seCurrentTime;
				s_pressed = GL_TRUE;
			}
			cameraPosition = v3_sub(cameraPosition, v3_muls(cameraFront, speed));
		}
		if (glfwGetKey(mainWindow._window, GLFW_KEY_S) == GLFW_RELEASE)
		{
			s_pressed = GL_FALSE;
		}

		//////////////////////////////////////////////////////////////a
		if (glfwGetKey(mainWindow._window, GLFW_KEY_A) == GLFW_PRESS)
		{
			if(!a_pressed)
			{
				velocityInputTime = seCurrentTime;
				a_pressed = GL_TRUE;
			}
			cameraPosition = v3_sub(cameraPosition, v3_muls(v3_cross(cameraFront, cameraUp), speed));
		}
		if (glfwGetKey(mainWindow._window, GLFW_KEY_A) == GLFW_RELEASE)
		{
			a_pressed = GL_FALSE;
		}

		//////////////////////////////////////////////////////////////d
    	if (glfwGetKey(mainWindow._window, GLFW_KEY_D) == GLFW_PRESS)
		{
			if(!d_pressed)
			{
				velocityInputTime = seCurrentTime;
				d_pressed = GL_TRUE;
			}
			cameraPosition = v3_add(cameraPosition, v3_muls(v3_cross(cameraFront, cameraUp), speed));
		}
		if (glfwGetKey(mainWindow._window, GLFW_KEY_D) == GLFW_RELEASE)
		{
			d_pressed = GL_FALSE;
		}


		if (glfwGetKey(mainWindow._window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(mainWindow._window, GLFW_TRUE);
		}

		GLfloat xoffset = xpos - lastX;
		GLfloat yoffset = lastY - ypos;

    	lastX = xpos;
    	lastY = ypos;

    	xoffset *= mouseSpeed;
    	yoffset *= mouseSpeed;

    	yaw   += xoffset;
    	pitch += yoffset;

    	if(pitch > 89.0f)
    	    pitch = 89.0f;
    	if(pitch < -89.0f)
    	    pitch = -89.0f;

    	cameraFront = v3_norm(vec3( 
				cos(radians(yaw)) * cos(radians(pitch)), 
				sin(radians(pitch)),
				sin(radians(yaw)) * cos(radians(pitch))
				));

		V = m4_lookAt(cameraPosition, v3_add(cameraPosition, cameraFront), cameraUp);
		//processing input end

		seObjectDrawArrays(&floor);

		glfwSwapBuffers(mainWindow._window);
		glfwPollEvents();
	}

	seShaderProgramDelete(&mainProgram);
	seWindowDestroy(&mainWindow);
	return 0;
}




