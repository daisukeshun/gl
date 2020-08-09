#ifndef CAMERA_H
#define CAMERA_H
#include <GL/glew.h>
#include "../math/math3d.h"

typedef struct seCameraCreateInfo
{
	
	vec3_t position;
	vec3_t direction;
	vec3_t up;
	

	GLfloat mouseSpeed;
	GLfloat speed;
	GLfloat motionSpeed;
	GLfloat mousePositionX;
	GLfloat mousePositionY;
	GLfloat verticalAngle;
	GLfloat horizontalAngle;

	GLfloat fov, aspect, znear, zfar;

	GLdouble x, y;

	GLchar cursor;

	mat4_t projection;
	mat4_t view;

} seCameraCreateInfo;

void seCameraUpdate(seCameraCreateInfo * camera);
void seCameraSeeTo(seCameraCreateInfo * camera, GLfloat x, GLfloat y, GLfloat z);
void seCameraMoveTo(seCameraCreateInfo * camera, GLfloat x, GLfloat y, GLfloat z);
#endif
