#include "../opengl/shaders.h"
#include "../utils/u_read.h"
#include "m_types.h"
#include <GL/glext.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

void setName(GLchar ** dest, const GLchar * string)
{
	*dest = (GLchar *)malloc(strlen(string));
	memset(*dest, '\0', strlen(string));
	strcpy(*dest, string);
}

ShaderGroup setShaderGroup(const GLchar * vssource, const GLchar * fssource, GLsizei count)
{
	ShaderGroup group;
	//group.memberCount = 0;
	group.memberCount = count;
	setName(&group.vs_source, vssource);
	setName(&group.fs_source, fssource);

	GLchar * text = u_read(group.vs_source);
	GLuint vs, fs;
	ShaderCreate(&vs, GL_VERTEX_SHADER, text);
	free(text);

	text = u_read(group.fs_source);
	ShaderCreate(&fs, GL_FRAGMENT_SHADER, text);
	free(text);

	ShaderProgramCreate(&group.programID, &vs, &fs);

	group.member = (Object*)calloc(count, sizeof(Object));
	//group.member = NULL;
	return group;
}


void deleteShaderGroup(ShaderGroup * group)
{
	free(group->name);
	free(group->fs_source);
	free(group->vs_source);
	GLsizei i;
	for(i = 0; i < group->memberCount; i++)
		deleteObject(&group->member[i]);
	glDeleteProgram(group->programID);
	group->programID = 0;
}

void loadObject(Object * objct)
{
	if(!objct->loaded)
	{
		glGenVertexArrays(1, &objct->vao);
		glBindVertexArray(objct->vao);
	
		glGenBuffers(1, &objct->vbo);
		glBindBuffer(GL_ARRAY_BUFFER, objct->vbo);
	
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * objct->v_size, (const void*)objct->vrts, GL_DYNAMIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
	}
	objct->loaded = GL_TRUE;
}

Object setObject(GLsizei vsize, GLsizei csize, GLsizei tsize)
{
	Object obj;

	obj.rotation = NULL;
	obj.position = NULL;
	obj.loaded = GL_FALSE;
	obj.v_size = vsize;
	obj.c_size = csize;
	obj.t_size = tsize;
	obj.clrs = obj.vrts = obj.txtr = NULL;
	obj.name = NULL;

	if(vsize != 0) 
		obj.vrts = (GLfloat*)calloc(obj.v_size, sizeof(GLfloat));
	if(csize != 0) 
		obj.clrs = (GLfloat*)calloc(obj.c_size, sizeof(GLfloat));
	if(tsize != 0) 
		obj.txtr = (GLfloat*)calloc(obj.t_size, sizeof(GLfloat));

	return obj;
}

void deleteObject(Object * objct)
{
	if(objct->name != NULL)
		free(objct->name);
	if(objct->v_size)
		free(objct->vrts);
	if(objct->c_size)
		free(objct->clrs);
	if(objct->t_size)
		free(objct->txtr);
	objct->vrts = objct->clrs = objct->txtr = NULL;
	objct->name = NULL;
}

void print_objct(Object * objct)
{
	GLsizei i;
	if(objct->name != NULL)
		printf("Object %s:\n", objct->name);
	printf("===================================\n");
	printf("Vertices:");
	if(objct->v_size != 0){
		for(i = 0; i < objct->v_size; i++)
		{
			i % 3 == 0 ? printf("\n") : 0;
			printf("%f ", objct->vrts[i]);
		}
	} else {
		printf("\nNULL\n");
	}
	printf("\nColors:");
	if(objct->c_size != 0){
		for(i = 0; i < objct->c_size; i++)
		{
			i % 4 == 0 ? printf("\n") : 0;
			printf("%f ", objct->clrs[i]);
		}
	} else {
		printf("\nNULL\n");
	}
	printf("\nTextures:");
	if(objct->t_size != 0){
		for(i = 0; i < objct->t_size; i++)
		{
			i % 2 == 0 ? printf("\n") : 0;
			printf("%f ", objct->txtr[i]);
		}
	} else {
		printf("\nNULL\n");
	}
	printf("===================================\n");
	printf("\n");
}
