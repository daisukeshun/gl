#pragma once
#include "types.h"

typedef struct {
	vec3f position;		//position of camera in world coords
	vec3f rotation;		//rotation of camera (in degrees)
	float zNear;		//min drawing Z coord
	float zFar;			//max drawing Z coord
	float POV;			//angle of view
	float aspectRatio;	//window width/window height
} Camera;				//camera type

#define defCamera(camera) Camera * camera = (Camera*)calloc(1, sizeof(Camera));

#define isCamera(camera);\
		isVec3f(camera->position);\
		isVec3f(camera->rotation);\
		camera->zNear		= 0;\
		camera->zFar		= 0;\
		camera->POV			= 0;\
		camera->aspectRatio	= 0;

#define setCamera(camera,\
	   	sPosition,\
	   	sRotation,\
	   	szNear,\
	   	szFar,\
	   	sPOV,\
	   	sAspectRatio)\
	setVec3(camera->position, sPosition[0], sPosition[1], sPosition[2]);\
	setVec3(camera->rotation, sRotation[0], sRotation[1], sRotation[2]);\
	camera->zNear		= szNear;\
	camera->zFar		= szFar;\
	camera->POV			= sPOV;\
	camera->aspectRatio = sAspectRatio;

#define delCamera(camera);\
	free(camera->position);\
	free(camera->rotation);\
	free(camera);
