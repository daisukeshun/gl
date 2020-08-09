#include "camera.h"

void seCameraUpdate(seCameraCreateInfo * camera)
{
	/*
	camera->projection = glm::perspective(camera->fov, camera->aspect, camera->znear, camera->zfar);

	camera->view = glm::lookAt(camera->position, 
								camera->position + camera->direction,
								camera->up);
	*/
}

void seCameraMoveTo(seCameraCreateInfo * camera, GLfloat x, GLfloat y, GLfloat z)
{
	camera->position.x += x;
	camera->position.y += y;
	camera->position.z += z;
	seCameraUpdate(camera);
}

void seCameraSeeTo(seCameraCreateInfo * camera, GLfloat x, GLfloat y, GLfloat z)
{
	camera->direction.x = x;
	camera->direction.y = y;
	camera->direction.z = z;
	seCameraUpdate(camera);
}
