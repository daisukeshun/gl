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
	glShaderSource(shader, 1, &text, NULL);
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

char seUniformMatrix(seShaderProgramCreateInfo * program, const GLchar * uniform, glm::mat4 matrix)
{
	glUseProgram(program->_id);
	unsigned int transformLoc = glGetUniformLocation(program->_id, uniform);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
	return 0;
}

char seUseProgram(seShaderProgramCreateInfo * program)
{
	glUseProgram(program->_id);
	return 0;
}
