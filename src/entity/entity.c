#include "entyty.h"

seRect seRectCreate(seShaderProgramCreateInfo * program)
{
	seRect rect;

	rect.color = glm::vec4(1.f);

	rect.position = glm::vec3(0);
	rect.rotation = glm::vec3(0);
	rect.scale = glm::vec3(1.f);

	rect.model = glm::mat4(1.f);
	rect.model = glm::translate(rect.model, rect.position);
	rect.model = glm::rotate(rect.model, rect.rotation.z * DEG2RAD, glm::vec3(0, 0, 1));
	rect.model = glm::rotate(rect.model, rect.rotation.y * DEG2RAD, glm::vec3(0, 1, 0));
	rect.model = glm::rotate(rect.model, rect.rotation.x * DEG2RAD, glm::vec3(1, 0, 0));
	rect.model = glm::scale(rect.model, rect.scale);

	rect.elemetDataSize = 36 * sizeof(GLuint);
	rect.vertexDataSize = 24 * sizeof(GLfloat);

	rect.elementData = (GLuint*)malloc(rect.elemetDataSize);
	rect.vertexData = (GLfloat*)malloc(rect.vertexDataSize);

	rect.vertexData[0] = -0.5;
	rect.vertexData[1] = -0.5;
	rect.vertexData[2] = -0.5;

	rect.vertexData[3] = -0.5;
	rect.vertexData[4] = 0.5;
	rect.vertexData[5] = -0.5;

	rect.vertexData[6] = 0.5;
	rect.vertexData[7] = 0.5;
	rect.vertexData[8] = -0.5;

	rect.vertexData[9] = 0.5;
	rect.vertexData[10] = -0.5;
	rect.vertexData[11] = -0.5;

	rect.vertexData[12] = -0.5;
	rect.vertexData[13] = -0.5;
	rect.vertexData[14] = 0.5;

	rect.vertexData[15] = -0.5;
	rect.vertexData[16] = 0.5;
	rect.vertexData[17] = 0.5;

	rect.vertexData[18] = 0.5;
	rect.vertexData[19] = 0.5;
	rect.vertexData[20] = 0.5;

	rect.vertexData[21] = 0.5;
	rect.vertexData[22] = -0.5;
	rect.vertexData[23] = 0.5;

	rect.elementData[0] = 0;
	rect.elementData[1] = 1;
	rect.elementData[2] = 2;

	rect.elementData[3] = 2;
	rect.elementData[4] = 3;
	rect.elementData[5] = 0;

	rect.elementData[6] = 0;
	rect.elementData[7] = 4;
	rect.elementData[8] = 1;

	rect.elementData[9] = 1;
	rect.elementData[10] = 5;
	rect.elementData[11] = 4;

	rect.elementData[12] = 4;
	rect.elementData[13] = 5;
	rect.elementData[14] = 6;

	rect.elementData[15] = 6;
	rect.elementData[16] = 7;
	rect.elementData[17] = 4;

	rect.elementData[18] = 2;
	rect.elementData[19] = 6;
	rect.elementData[20] = 7;

	rect.elementData[21] = 2;
	rect.elementData[22] = 3;
	rect.elementData[23] = 7;

	rect.elementData[24] = 0;
	rect.elementData[25] = 4;
	rect.elementData[26] = 7;

	rect.elementData[27] = 7;
	rect.elementData[28] = 3;
	rect.elementData[29] = 0;

	rect.elementData[30] = 1;
	rect.elementData[31] = 5;
	rect.elementData[32] = 6;

	rect.elementData[33] = 6;
	rect.elementData[34] = 2;
	rect.elementData[35] = 1;

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
	glDrawElements(GL_TRIANGLES, rect->elemetDataSize / sizeof(GLfloat), GL_UNSIGNED_INT, 0);
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
