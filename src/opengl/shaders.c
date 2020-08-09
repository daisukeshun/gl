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

char seUniformMatrix(seShaderProgramCreateInfo * program, const GLchar * uniform, mat4_t * matrix)
{
	glUseProgram(program->_id);
	unsigned int transformLoc = glGetUniformLocation(program->_id, uniform);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, matrix->raw);
	return 0;
}

char seUniformVector(seShaderProgramCreateInfo * program, const GLchar * uniform, vec4_t * color)
{
	glUseProgram(program->_id);
	unsigned int transformLoc = glGetUniformLocation(program->_id, uniform);
	glUniform4fv(transformLoc, 1, color->raw);
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

