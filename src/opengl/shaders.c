#include "shaders.h"

char ShaderCreate(GLuint *id, GLenum shaderType, const char * source)
{
	*id = glCreateShader(shaderType);
	glShaderSource(*id, 1, &source, NULL);
	glCompileShader(*id);

	int success = 0;
	char infoLog[512] = { 0 };
	glGetShaderiv(*id, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(*id, 512, NULL, infoLog);
		printf("Shader is not compiled\n%s\n", infoLog);
	};

	return 0;
}


char ShaderProgramCreate(GLuint * id, GLuint *vshader, GLuint *fshader)
{
	int success = 0;
	char infoLog[512] = { 0 };
	*id = glCreateProgram();
	glAttachShader(*id, *vshader);
	glAttachShader(*id, *fshader);
	glLinkProgram(*id);

	glGetProgramiv(*id, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(*id, 512, NULL, infoLog);
		printf("Program is not compiled\n%s\n", infoLog);
	}

	glDeleteShader(*vshader);
	glDeleteShader(*fshader);

	*vshader = *fshader = 0;
	return 0;
}

char setUniformMatrix(GLuint id, const GLchar * uniform, GLsizei count, GLboolean transpose, const GLfloat * value)
{
	glUniformMatrix4fv(glGetUniformLocation(id, uniform), count, transpose, value);
	return 0;
}
