#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../opengl/shaders.h"

#define DEG2RAD 0.0174533f

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

seRect seRectCreate(seShaderProgramCreateInfo * program);
void seRectModelUpdate(seRect * rect);
void seRectDraw(seRect * rect);
char seDeleteRect(seRect * rect);
