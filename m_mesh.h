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
	array  V_DATA, 
		   F_DATA;
	

	GLenum DATA_TYPE;
	GLboolean NORMALIZE;
	GLint V_COMPONENTS;
	GLsizei STRIDE;
} Mesh;

typedef struct scene{
	Mesh * objects;
	unsigned long objectsCount;
	unsigned long NUM_VERTICES;
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
} scene;

typedef struct MeshUtil{
	void (*load)(array * v, array * f, char * path);
	void (*draw)(Mesh mesh);
	void (*del)(Mesh * mesh);
} MeshUtil;

void MeshUtil_Draw(Mesh mesh){
}

void MeshUtil_Load(array * V, array * F, char * path){
	ArrayUtil aUtil = createArrayUtil();
	FILE *file;
    char line[1024];
	char fsc, fwc, fdc;
	unsigned int vc, fc, vtc, vnc;
	vc = fc = vtc = vnc = fsc = fwc = fdc = 0;
    file = fopen(path, "r");

	GLfloat * v = calloc(1, sizeof(GLfloat));
	GLuint * f	= calloc(1, sizeof(GLuint));

    if (file == NULL){
		printf("file not found");
		nl;
	}
	while(!feof(file)){
		fgets(line, 1023, file);
		if(line[0] == 'v'){
			if(line[1] == ' '){
				vc+=3;
				v = realloc(v, sizeof(GLfloat) * vc);
				sscanf(line, "v %f %f %f\n", 
						&v[vc - 3], &v[vc - 2], &v[vc - 1]);
			}
			if(line[1] == 't'){
				vtc+=3;
			}
			if(line[1] == 'n'){
				vnc+=3;
			}
		}
		if(line[0] == 'f'){
			if(!fwc){
				unsigned int j;
				for(j = 0; j < strlen(line); j++){
					if(line[j] == '/'){
						fsc++;
					}
				}
				if(line[4] == '/'){
					fdc = 1;
				}
				fwc = 1;
				fsc += 3;
			}
			fc+=fsc;
			f = realloc(f, sizeof(GLuint) * fc);
			switch (fsc){
				case 3:
					{
						sscanf(line, "f %u %u %u\n",
								&f[fc - 3], &f[fc - 2], &f[fc - 1]);
					}
					break;
				case 6:
					{
						sscanf(line, "f %u/%u %u/%u %u/%u\n",
								&f[fc - 6], &f[fc - 5], &f[fc - 4],
								&f[fc - 3], &f[fc - 2], &f[fc - 1]);
					}
					break;
				case 9:
					{
						sscanf(line, "f %u/%u/%u %u/%u/%u %u/%u/%u\n",
								&f[fc - 9], &f[fc - 8], &f[fc - 7],
								&f[fc - 6], &f[fc - 5], &f[fc - 4],
								&f[fc - 3], &f[fc - 2], &f[fc - 1]);
					}
					break;
			}
		}
	}
    fclose(file);

	
	*V = aUtil.array(FLOAT, vc);
	*F = aUtil.array(UINT, fc);

	aUtil.copy(V, v, V->len);

	fsc/=3;
	unsigned int i, counter;
	counter = 0;
	for(i = 0; i < F->len; i+=fsc){
		F->ui[counter] = f[i] - 1;
		counter++;
	};
	free(f);
	free(v);
}

MeshUtil createMeshUtil(){
	MeshUtil ret;
	ret.draw = MeshUtil_Draw;
	ret.load = MeshUtil_Load;
	return ret;
}
#endif
/*
*/
