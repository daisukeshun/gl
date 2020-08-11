#ifndef SHADERS_H
#define SHADERS_H
#include <GL/glew.h>
#include "../utils/u_read.h"
#include "../math/math3d.h"
#include <GLFW/glfw3.h>

typedef struct seShaderProgramCreateInfo
{
	const GLchar * vertexShaderFilePath;
	const GLchar * fragmentShaderFilePath;
	GLuint _id;
} seShaderProgramCreateInfo;

GLuint seLoadShader(GLenum shaderType, const char * path);
void seShaderProgramCreate(seShaderProgramCreateInfo * program);
void seShaderLinkingCheck(GLuint id);
void seShaderProgramUse(seShaderProgramCreateInfo * program);
void seShaderProgramDelete(seShaderProgramCreateInfo * program);
#endif
