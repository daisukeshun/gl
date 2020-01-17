#ifndef MESHUTIL_H
#define MESHUTIL_H
#include "m_utils.h"
#include "m_array.h"
#include <GL/glew.h>


typedef struct Mesh{
	char * path;
	GLuint vao, vbo;
	GLuint NUM_VERTICES,
		   NUM_FACES,
		   NUM_LINES,
		   NUM_TEXTURES,
		   DATA_OFFSET,
		   DATA_SIZE;

	GLenum DATA_TYPE;
	GLboolean NORMALIZE;
	GLint V_COMPONENTS;
	GLsizei STRIDE;
} Mesh;

typedef struct MeshUtil{
	Mesh (*load)(char * path);
	void (*draw)(Mesh mesh);
	void (*del)(Mesh * mesh);
} MeshUtil;


Mesh MeshUtil_Load(char * path){
	Mesh ret;
	ret.path = path;

	char * text = ReadFile(path);
	unsigned int i;

	ret.NUM_FACES = 
	ret.NUM_LINES = 
	ret.NUM_TEXTURES = 
	ret.NUM_VERTICES = 0;
	for(i = 0; i < strlen(text); i++){
		if(text[i] == '\n'){
			ret.NUM_LINES++;
		}
		if(text[i] == 'v' && text[i+1] == ' '){
			ret.NUM_VERTICES++;
		}
		if(text[i] == 'f' && text[i+1] == ' '){
			ret.NUM_FACES++;
		}
		if(text[i] == 'v' && text[i+1] == 't'){
			ret.NUM_TEXTURES++;
		}
	}
	free(text);

	GLfloat *verts = (GLfloat*)calloc(ret.NUM_VERTICES, FSIZE);
	GLfloat *textrs = (GLfloat*)calloc(ret.NUM_TEXTURES, FSIZE);
	GLuint *faces = (GLuint*)calloc(ret.NUM_FACES, UISIZE);


	FILE * file = fopen(path, "r");

	GLfloat v[3], vt[3];
	GLuint f[6];
	unsigned int vc, fc, tc;

	vc = fc = tc = 0;
	for(i = 0; i < ret.NUM_LINES; i++){
		fscanf(file, "v %f %f %f\n", &v[0], &v[1], &v[2]);
		vc+=3;
		verts[vc - 3] = v[0];
		verts[vc - 2] = v[1];
		verts[vc - 1] = v[2];

		fscanf(file, "f %u/%u %u/%u %u/%u\n", &f[0], &f[1], &f[2], &f[3], &f[4], &f[5]);
		fc+=6;
		faces[fc - 6] = f[0];
		faces[fc - 5] = f[1];
		faces[fc - 4] = f[2];
		faces[fc - 3] = f[3];
		faces[fc - 2] = f[4];
		faces[fc - 1] = f[5];

		fscanf(file, "vt %f %f %f\n", &vt[0], &vt[1], &vt[2]);
		tc+=3;
		textrs[tc - 3] = vt[0];
		textrs[tc - 2] = vt[1];
		textrs[tc - 1] = vt[2];

	}

	fclose(file);

	glGenVertexArrays(1, &ret.vao);
	glBindVertexArray(ret.vao);

	glGenBuffers(1, &ret.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ret.vbo);

	ret.DATA_SIZE = ret.NUM_VERTICES * sizeof(*verts);
	glBufferData(GL_ARRAY_BUFFER, ret.DATA_SIZE, verts, GL_DYNAMIC_DRAW);

	glBindVertexArray(0);

	free(verts);
	free(textrs);
	free(faces);
	return ret;
}

void MeshUtil_Draw(Mesh mesh){
	glVertexAttribPointer(mesh.DATA_OFFSET, mesh.V_COMPONENTS, mesh.DATA_TYPE, mesh.NORMALIZE, mesh.STRIDE, 0);
}

MeshUtil createMeshUtil(){
	MeshUtil ret;
	ret.load = MeshUtil_Load;
	ret.draw = MeshUtil_Draw;
	return ret;
}
#endif
