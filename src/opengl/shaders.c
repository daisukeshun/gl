#include "shaders.h"

char seShaderLinkingCheck(GLuint id)
{
	int  success;
	char infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		 glGetShaderInfoLog(id, 512, NULL, infoLog);
		 printf("Vertex shader compile error: %s", infoLog);
	}
	return 0;
}

GLuint seLoadShader(GLenum shaderType, const char * path)
{
	GLuint shader = glCreateShader(shaderType);
	char * text = u_read(path);
	glShaderSource(shader, 1, (const GLchar * const*)&text, NULL);
	glCompileShader(shader);
	free(text);
	return shader;
}

char seShaderProgramCreate(seShaderProgramCreateInfo * program)
{

	GLuint vs, fs;

	vs = seLoadShader(GL_VERTEX_SHADER, program->vertexShaderFilePath);
	seShaderLinkingCheck(vs);

	fs = seLoadShader(GL_FRAGMENT_SHADER, program->fragmentShaderFilePath);
	seShaderLinkingCheck(fs);

	program->_id = glCreateProgram();

	glAttachShader(program->_id, vs);
	glAttachShader(program->_id, fs);

	glLinkProgram(program->_id);

	glDeleteShader(vs);
	glDeleteShader(fs);

 	return 0;
}

char seUseProgram(seShaderProgramCreateInfo * program)
{
	glUseProgram(program->_id);
	return 0;
}

char seShaderProgramDelete(seShaderProgramCreateInfo * program)
{
	program->fragmentShaderFilePath = "\0";
	program->vertexShaderFilePath = "\0";
	glDeleteProgram(program->_id);
	program->_id = 0;
	return 0;
}

