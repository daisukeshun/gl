#include <GL/glew.h>
#include <glm/glm.hpp>
#include <stdio.h>

typedef struct seCollisionRectCreateInfo
{
	GLfloat x0, y0, z0;
	GLfloat x1, y1, z1;
	GLfloat width, height;
	GLchar state;
} seCollisionRectCreateInfo;

typedef struct seCollisionCircleCreateInfo
{
	GLfloat x, y, z;
	GLfloat radius;
	GLchar state;
} seCollisionCircleCreateInfo;

typedef struct seCollisionPointCreateInfo
{
	GLfloat x, y, z;
	GLchar state;
} seCollisionPointCreateInfo;

GLchar seCollisionRectInit(seCollisionRectCreateInfo * r);
GLchar seCollisionCircleInit(seCollisionCircleCreateInfo * c);
GLchar seCollisionPointInit(seCollisionPointCreateInfo * p);

GLchar seRRColisionDetect(seCollisionRectCreateInfo * rect1, seCollisionRectCreateInfo * rect2);
GLchar seCCColisionDetect(seCollisionCircleCreateInfo * c1, seCollisionCircleCreateInfo * c2);
GLchar seRPCollisionDetect();
GLchar seCPCollisionDetect();


