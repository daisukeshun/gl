#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

typedef struct ShaderProgramCreateInfo
{
	GLuint _id;
	const GLchar * vertexShaderSource;
	const GLchar * fragmentShaderSource;
} ShaderProgramCreateInfo;

char ShaderCreate(GLuint *id, GLenum shaderType, const char * source);
char ShaderProgramCreate(ShaderProgramCreateInfo * program);
char setUniformMatrix4f(GLuint id, const GLchar * uniform, const GLfloat * value);

