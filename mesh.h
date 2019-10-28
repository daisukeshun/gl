#pragma once
#include "graphics.h"

typedef struct {
	vec3f position;			//in world coords
	vec3f rotation;			//in radians
	Triangle4f * polygons;	//in object coords
	vec3f * normals;		//from object
	unsigned int polNum;	//number of polygons/normals
} Mesh;

//generations of empty normals and polygons
void isNormals(vec3f * ret, const int number){
	ret = (vec3f *)calloc(number, sizeof(vec3f));
	for (int i = 0; i < number; i++){
		isVec3f(ret[i]);
	}
}

void isPolygons(Triangle4f * ret, const int number){
	ret = (Triangle4f *)calloc(number, sizeof(Triangle4f));
	for (int i = 0; i < number; i++){
		isTriangle4f(ret[i]);
	}
}
//generations of empty normals and polygons

#define defMesh(mesh) Mesh * mesh = (Mesh *)calloc(1, sizeof(Mesh));
#define isMesh(mesh)		 mesh = (Mesh *)calloc(1, sizeof(Mesh));

#define delMesh(mesh)\
	for(unsigned int i = 0; i < mesh->polNum){ \
		delVec(mesh->normals[i]);\
		delTriangle(mesh->polygons[i]);\
	};\
	delVec(mesh->position);\
	delVec(mesh->rotation);\
	free(mesh);
