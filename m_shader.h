#pragma once
#ifndef SHADERUTIL_H
#define SHADERUTIL_H
#include "m_utils.h"
#include "m_array.h"
#include <GL/glew.h>

typedef struct ShaderUtil{
	GLuint(*shader)(char* shaderSource, GLenum shaderType);
	GLuint(*program)(char * vertexShader, char * fragmentShader);
	void(*use)(GLuint shaderProgramID);
	void(*del)(GLuint shaderProgramID);
	void(*push)(GLuint *vao, GLuint *vbo, GLuint *ibo, array * vertices, array * indices, GLenum drawType);
} ShaderUtil;

GLuint ShaderUtil_Shader(char * shaderFile, GLenum shaderType){
	GLuint shader = glCreateShader(shaderType);

	const char * shaderSource = ReadFile(shaderFile);

	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	GLint err;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &err);

	if(err == GL_FALSE){
	int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		GLchar * errStr = (GLchar*)calloc(length+1, sizeof(GLchar));
		glGetShaderInfoLog(shader, length, &length, errStr);

		fprintf(stderr, "Shader compilation error:%s", errStr);
		free(errStr);
	}
	free((void*)shaderSource);

	return shader;
}

GLuint ShaderUtil_Program(char * vertexShadeFile, char * fragmentShaderFile){

	char * fileName = NULL;
	GLuint shaderProgram = glCreateProgram();

	fileName = vertexShadeFile;
	GLuint vs = ShaderUtil_Shader(fileName, GL_VERTEX_SHADER);

	fileName = fragmentShaderFile;
	GLuint fs = ShaderUtil_Shader(fileName, GL_FRAGMENT_SHADER);

	glAttachShader(shaderProgram, vs);
	glAttachShader(shaderProgram, fs);

	glBindAttribLocation(shaderProgram, 0, "program");

	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return shaderProgram;
}

void ShaderUtil_Push(GLuint *vao, GLuint *vbo, GLuint *ibo, array * vertices, array * indices, GLenum drawType){
	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);

	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices->size, vertices->f, drawType);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(*vertices->f), 0);

	glGenBuffers(1, ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size, indices->ui, drawType);
}

void ShaderUtil_Use(GLuint program){
	glUseProgram(program);
}

void ShaderUtil_Delete(GLuint program){
	glUseProgram(0);
	glDeleteProgram(program);
}

ShaderUtil createShaderUtil(void){
	ShaderUtil ret;

	ret.push	= ShaderUtil_Push;
	ret.shader	= ShaderUtil_Shader;
	ret.program	= ShaderUtil_Program;
	ret.use		= ShaderUtil_Use;
	ret.del		= ShaderUtil_Delete;

	return ret;
}
#endif
