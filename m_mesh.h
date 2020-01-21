#ifndef MESHUTIL_H
#define MESHUTIL_H
#include "m_utils.h"
#include "m_array.h"
#include <GL/glew.h>


typedef struct Mesh{
	char * path;
	GLuint vao, vbo, ibo;
	GLuint NUM_VERTICES,
		   NUM_NORMALS,
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
	ArrayUtil aUtil = createArrayUtil();
	Mesh ret;
	ret.path = path;

	char * text = ReadFile(path);
	unsigned int i;

	ret.NUM_FACES		= 
	ret.NUM_LINES		= 
	ret.NUM_NORMALS		=
	ret.NUM_TEXTURES	= 
	ret.NUM_VERTICES	= 0;

	for(i = 0; i < strlen(text); i++){
		if(text[i] == '\n'){
			ret.NUM_LINES++;
		}
		if(text[i] == 'v' && text[i+1] == ' '){
			ret.NUM_VERTICES+=3;
		}
		if(text[i] == 'f' && text[i+1] == ' '){
			ret.NUM_FACES++;
		}
		if(text[i] == 'v' && text[i+1] == 't'){
			ret.NUM_TEXTURES+=3;
		}
		if(text[i] == 'v' && text[i+1] == 'n'){
			ret.NUM_NORMALS+=3;
		}
	}
	free(text);

	/*GLfloat *v= (GLfloat*)calloc(ret.NUM_VERTICES, FSIZE);*/
	array v = aUtil.array(FLOAT, ret.NUM_VERTICES);
	array ret_v = aUtil.array(FLOAT, ret.NUM_FACES * 3);
	GLfloat *vn= (GLfloat*)calloc(ret.NUM_NORMALS, FSIZE);
	GLfloat *vt= (GLfloat*)calloc(ret.NUM_TEXTURES, FSIZE);
	GLuint *f= (GLuint*)calloc(1, UISIZE);

	FILE * file = fopen(path, "r");

	unsigned int vc, fc, tc, nc;

	char fsc = 0, fwc = 0;			/*f slash counter and f was counted*/

	vc = fc = tc = nc = 0;
	char* s = NULL;
	for(i = 0; i < ret.NUM_LINES; i++){
		s = ReadLine(file);
		if(s[0] == 'v' && s[1] == ' '){
			sscanf(s, "v %f %f %f\n", &v.f[vc + 0], &v.f[vc + 1], &v.f[vc + 2]);
			vc+=3;
		}
		if(s[0] == 'v' && s[1] == 't'){
			sscanf(s, "vt %f %f %f\n", &vt[tc + 0], &vt[tc + 1], &vt[tc + 2]);
			tc+=3;
		}
		if(s[0] == 'v' && s[1] == 'n'){
			sscanf(s, "vn %f %f %f\n", &vn[nc + 0], &vn[nc + 1], &vn[nc + 2]);
			nc+=3;
		}
		if(s[0] == 'f' && s[1] == ' '){
			if(!fwc){
				unsigned int j;
				for(j = 0; j < strlen(s); j++){
					if(s[j] == '/'){
						fsc++;
					}
				}
				fwc++;
				f = realloc(f, sizeof(unsigned int) * ret.NUM_FACES * (fsc + 1));
		} 
		switch (fsc){
			case 0:
			{
				sscanf(s, "f %u %u %u\n", 
					&f[fc+0], &f[fc+1], &f[fc+2]);
				fc+=3;
			}
			break;
			case 3:
			{
				sscanf(s, "f %u/%u %u/%u %u/%u\n", 
					&f[fc+0], &f[fc+1], &f[fc+2],
				   	&f[fc+3], &f[fc+4], &f[fc+5]);
				fc+=6;
			}
			break;
			case 6:
			{
				sscanf(s, "f %u/%u/%u %u/%u/%u %u/%u/%u\n", 
					&f[fc+0], &f[fc+1], &f[fc+2],
				   	&f[fc+3], &f[fc+4], &f[fc+5],
				   	&f[fc+6], &f[fc+7], &f[fc+8]
				  );
				fc+=9;
			}
			break;
			}
		}
	}


	glGenVertexArrays(1, &ret.vao);
	glBindVertexArray(ret.vao);

	fsc /= 2;
	unsigned int index;
	int count = 0;
	for(i = 0; i < ret.NUM_FACES * 3; i++){	
		index = f[i*fsc];
		ret_v.f[count] =  v.f[index];
		count++;
	}

	ret.DATA_SIZE = ret_v.size;
	ret.NUM_VERTICES = ret_v.len;
	ret.DATA_OFFSET = 0;
	ret.V_COMPONENTS = 3;
	ret.DATA_TYPE = GL_FLOAT;
	ret.STRIDE = 3 * sizeof(*ret_v.f);
	ret.NORMALIZE = GL_FALSE;

	glGenBuffers(1, &ret.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ret.vbo);

	glBufferData(GL_ARRAY_BUFFER, ret.DATA_SIZE, ret_v.f, GL_DYNAMIC_DRAW);

	glBindVertexArray(0);

	aUtil.del(&v);
	aUtil.del(&ret_v);
	free(vn);
	free(vt);
	free(f);
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
/*
*/
