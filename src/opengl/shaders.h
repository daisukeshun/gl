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

char seShaderProgramCreate(seShaderProgramCreateInfo * program);
GLuint seLoadShader(GLenum shaderType, const char * path);
char seShaderLinkingCheck(GLuint id);
char seUniformMatrix(seShaderProgramCreateInfo * program, const GLchar * uniform, mat4_t * matrix);
char seUniformVector(seShaderProgramCreateInfo * program, const GLchar * uniform, vec4_t * color);
char seUseProgram(seShaderProgramCreateInfo * program);
char seShaderProgramDelete(seShaderProgramCreateInfo * program);
#endif
