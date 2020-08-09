#include "control.h"

void seInputFunction(seWindowCreateInfo * window, seCameraCreateInfo * camera)
{
	if(glfwGetKey(window->_window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{	
		glfwSetInputMode(window->_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		camera->cursor = 1;
	}
	if(glfwGetKey(window->_window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
	{
		glfwSetInputMode(window->_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPos(window->_window, window->width/2, window->height/2);
		camera->cursor = 0;
	}

	if(glfwGetKey(window->_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window->_window, GL_TRUE);

	if (glfwGetKey(window->_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera->speed = 10.f;

	if (glfwGetKey(window->_window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
		camera->speed = 2.5f;

	if (glfwGetKey(window->_window, GLFW_KEY_W) == GLFW_PRESS)
		NULL;

        //camera->position += camera->motionSpeed * camera->direction;

    if (glfwGetKey(window->_window, GLFW_KEY_S) == GLFW_PRESS)
		NULL;
        //camera->position -= camera->motionSpeed * camera->direction;

    if (glfwGetKey(window->_window, GLFW_KEY_A) == GLFW_PRESS)
		NULL;
		
        //camera->position -= glm::normalize(glm::cross(camera->direction, camera->up)) * camera->mouseSpeed;
    if (glfwGetKey(window->_window, GLFW_KEY_D) == GLFW_PRESS)
		NULL;
        //camera->position += glm::normalize(glm::cross(camera->direction, camera->up)) * camera->mouseSpeed;
}

void seMouseInputFunction(seWindowCreateInfo * window, seCameraCreateInfo * camera)
{
	glfwGetCursorPos(window->_window, &camera->x, &camera->y);
	GLfloat centerx = window->width / 2, 
			centery = window->height / 2;
	GLfloat offsetx, offsety;
	GLfloat sensitivity = 0.1f;

	if(camera->cursor == 0)
	{
		offsetx		=	camera->x - centerx;
		offsety		=	camera->y - centery; 
    	offsetx		*=	sensitivity;
    	offsety		*=	sensitivity;

		camera->verticalAngle -= offsety;
		camera->horizontalAngle += offsetx;

		if(camera->verticalAngle > 89.0f)
		{
    	    camera->verticalAngle = 89.0f;
		}
    	if(camera->verticalAngle < -89.0f)
		{
    	    camera->verticalAngle = -89.0f;
		}

		camera->direction.x = 
			cosf(radians(camera->horizontalAngle)) * cosf(radians(camera->verticalAngle));
    	camera->direction.y = 
			sinf(radians(camera->horizontalAngle)) * cosf(radians(camera->verticalAngle));
    	camera->direction.z = 
			sinf(radians(camera->verticalAngle));

		sv3_norm(&camera->direction);
	}

	if(!camera->cursor)
	{
		glfwSetCursorPos(window->_window, centerx, centery);
	}
}
