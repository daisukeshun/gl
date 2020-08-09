#ifndef ENTITY_H
#define ENTITY_H
#include <GL/glew.h>
#include "../opengl/shaders.h"
#include "../physics/collision.h"

/*
#define SE_OBJECT_MODEL_UPDATE(object)\
	object.model = glm::mat4(1.f);\
	object.model = glm::translate(object.model, object.position);\
	object.model = glm::rotate(object.model, object.rotation.z, glm::vec3(0, 0, 1));\
	object.model = glm::rotate(object.model, object.rotation.y, glm::vec3(0, 1, 0));\
	object.model = glm::rotate(object.model, object.rotation.x, glm::vec3(1, 0, 0));\
	object.model = glm::scale(object.model, object.scale);
*/

#define SE_OBJECT_DRAW(object)\
	glBindVertexArray(object.vao);\
	glDrawElements(GL_TRIANGLES, object.elemetDataSize / sizeof(GLfloat), GL_UNSIGNED_INT, 0);\
	glBindVertexArray(0);

#define SE_OBJECT_DELETE(object)\
	free(object.elementData);\
	free(object.vertexData);\
	object.elemetDataSize = 0;\
	object.vertexDataSize = 0;\
	object.shaderProgramId = 0;\
	glDeleteBuffers(1, &object.ebo);\
	glDeleteBuffers(1, &object.vbo);\
	glDeleteVertexArrays(1, &object.vao);

typedef struct seMesh_t
{
	vec3_t axis;
	vec3_t position;
	vec3_t rotation;
	vec3_t scale;
	vec4_t color;
	mat4_t model;

	GLfloat * vertexData;
	GLuint * elementData;
	GLuint vertexDataSize;
	GLuint elemetDataSize;

	GLuint vao, vbo, ebo;

} seMesh_t;

typedef struct seObject_t
{
	GLuint shaderProgramId;
	seMesh_t * mesh;
} seObject_t;

typedef struct seRect
{
	vec3_t axis;
	vec3_t position;
	vec3_t rotation;
	vec3_t scale;
	vec4_t color;

	mat4_t model;

	GLfloat * vertexData;
	GLuint * elementData;
	GLuint vertexDataSize;
	GLuint elemetDataSize;

	GLuint vao, vbo, ebo;
	GLuint shaderProgramId;
} seRect;
seRect seRectCreate(seShaderProgramCreateInfo * program);

typedef struct sePlane
{
	vec3_t axis;
	vec3_t position;
	vec3_t rotation;
	vec3_t scale;
	vec4_t color;

	mat4_t model;

	GLfloat * vertexData;
	GLuint * elementData;
	GLuint vertexDataSize;
	GLuint elemetDataSize;

	GLuint vao, vbo, ebo;
	GLuint shaderProgramId;
} sePlane;
sePlane sePlaneCreate(seShaderProgramCreateInfo * program);

#endif
