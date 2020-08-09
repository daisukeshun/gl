#include "entyty.h"
#include <string.h>

seRect seRectCreate(seShaderProgramCreateInfo * program)
{
	seRect rect;

	/*	5 6
	 *	4 7
	 * 1 2
	 * 0 3
	 */


	rect.color = vec4(1.f, 1.f, 1.f, 1.f);

	rect.position = vec3(0, 0, 0);
	rect.rotation = vec3(0, 0, 0);
	rect.scale = vec3(1.f, 1.f, 1.f);

	/*
	rect.model = mat4(1.f);
	rect.model = translate(rect.model, rect.position);
	rect.model = rotate(rect.model, rect.rotation.z, vec3(0, 0, 1));
	rect.model = rotate(rect.model, rect.rotation.y, vec3(0, 1, 0));
	rect.model = rotate(rect.model, rect.rotation.x, vec3(1, 0, 0));
	rect.model = scale(rect.model, rect.scale);
	 */

	rect.elemetDataSize = 36 * sizeof(GLuint);
	rect.vertexDataSize = 24 * sizeof(GLfloat);

	rect.elementData = (GLuint*)malloc(rect.elemetDataSize);
	rect.vertexData = (GLfloat*)malloc(rect.vertexDataSize);

	memset((void*)rect.elementData, 0, rect.elemetDataSize);
	memset((void*)rect.vertexData, 0, rect.vertexDataSize);

	rect.vertexData[0] = -0.5;
	rect.vertexData[2] = -0.5;

	rect.vertexData[3] = -0.5;
	rect.vertexData[4] = 1.0;
	rect.vertexData[5] = -0.5;

	rect.vertexData[6] = 0.5;
	rect.vertexData[7] = 1.0;
	rect.vertexData[8] = -0.5;

	rect.vertexData[9] = 0.5;
	rect.vertexData[11] = -0.5;

	rect.vertexData[12] = -0.5;
	rect.vertexData[14] = 0.5;

	rect.vertexData[15] = -0.5;
	rect.vertexData[16] = 1.0;
	rect.vertexData[17] = 0.5;

	rect.vertexData[18] = 0.5;
	rect.vertexData[19] = 1.0;
	rect.vertexData[20] = 0.5;

	rect.vertexData[21] = 0.5;
	rect.vertexData[23] = 0.5;

	rect.elementData[0] = 0;
	rect.elementData[1] = 1;
	rect.elementData[2] = 2;

	rect.elementData[3] = 2;
	rect.elementData[4] = 3;
	rect.elementData[5] = 0;

	rect.elementData[6] = 5;
	rect.elementData[7] = 1;
	rect.elementData[8] = 0;

	rect.elementData[9] = 0;
	rect.elementData[10] = 4;
	rect.elementData[11] = 5;

	rect.elementData[12] = 3;
	rect.elementData[13] = 2;
	rect.elementData[14] = 6;

	rect.elementData[15] = 6;
	rect.elementData[16] = 7;
	rect.elementData[17] = 3;

	rect.elementData[18] = 7;
	rect.elementData[19] = 6;
	rect.elementData[20] = 5;

	rect.elementData[21] = 5;
	rect.elementData[22] = 4;
	rect.elementData[23] = 7;

	rect.elementData[24] = 1;
	rect.elementData[25] = 5;
	rect.elementData[26] = 6;

	rect.elementData[27] = 6;
	rect.elementData[28] = 2;
	rect.elementData[29] = 1;

	rect.elementData[30] = 4;
	rect.elementData[31] = 0;
	rect.elementData[32] = 3;

	rect.elementData[33] = 3;
	rect.elementData[34] = 7;
	rect.elementData[35] = 4;

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

sePlane sePlaneCreate(seShaderProgramCreateInfo * program)
{
	sePlane plane;

	/* 1 2
	 * 0 3
	 *
	 */
	plane.color = vec4(1.f, 1.f, 1.f, 1.f);
                                            
	plane.position = vec3(0, 0, 0);
	plane.rotation = vec3(0, 0, 0);
	plane.scale = vec3(1.f, 1.f, 1.f);

	/*
	plane.model = glm::mat4(1.f);
	plane.model = glm::translate(plane.model, plane.position);
	plane.model = glm::rotate(plane.model, plane.rotation.z, glm::vec3(0, 0, 1));
	plane.model = glm::rotate(plane.model, plane.rotation.y, glm::vec3(0, 1, 0));
	plane.model = glm::rotate(plane.model, plane.rotation.x, glm::vec3(1, 0, 0));
	plane.model = glm::scale(plane.model, plane.scale);
	 */

	plane.elemetDataSize = 6 * sizeof(GLuint);
	plane.vertexDataSize = 12 * sizeof(GLfloat);

	plane.elementData = (GLuint*)malloc(plane.elemetDataSize);
	plane.vertexData = (GLfloat*)malloc(plane.vertexDataSize);

	memset((void*)plane.elementData, 0, plane.elemetDataSize);
	memset((void*)plane.vertexData, 0, plane.vertexDataSize);

	plane.vertexData[0] = -0.5;
	plane.vertexData[1] = -0.5;

	plane.vertexData[3] = -0.5;
	plane.vertexData[4] = 0.5;

	plane.vertexData[6] = 0.5;
	plane.vertexData[7] = 0.5;

	plane.vertexData[9] = 0.5;
	plane.vertexData[10] = -0.5;

	plane.elementData[0] = 0;
	plane.elementData[1] = 1;
	plane.elementData[2] = 2;

	plane.elementData[3] = 2;
	plane.elementData[4] = 3;
	plane.elementData[5] = 0;

	glGenVertexArrays(1, &plane.vao);
	glBindVertexArray(plane.vao);

	glGenBuffers(1, &plane.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, plane.vbo);
	glBufferData(GL_ARRAY_BUFFER, plane.vertexDataSize, plane.vertexData, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &plane.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, plane.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, plane.elemetDataSize, plane.elementData, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	plane.shaderProgramId = program->_id;

	glBindVertexArray(0);
	return plane;
}

