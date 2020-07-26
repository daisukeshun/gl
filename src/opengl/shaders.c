#include "shaders.h"

char ShaderCreate(GLuint *id, GLenum shaderType, const GLchar * source)
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


char ShaderProgramCreate(ShaderProgramCreateInfo * program)
{
	int success = 0;
	char infoLog[512] = { 0 };
	program->_id = glCreateProgram();
	GLuint vshader, fshader;


	ShaderCreate(&vshader, GL_VERTEX_SHADER, program->vertexShaderSource);
	ShaderCreate(&fshader, GL_FRAGMENT_SHADER, program->fragmentShaderSource);

	glAttachShader(program->_id, vshader);
	glAttachShader(program->_id, fshader);
	glLinkProgram(program->_id);

	glGetProgramiv(program->_id, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(program->_id, 512, NULL, infoLog);
		printf("Program is not compiled\n%s\n", infoLog);
	}

	glDeleteShader(vshader);
	glDeleteShader(fshader);
	return 0;
}

char setUniformMatrix4f(GLuint id, const GLchar * uniform, const GLfloat * value)
{
	glUniformMatrix4fv(glGetUniformLocation(id, uniform), 1, GL_FALSE, value);
	return 0;
}
