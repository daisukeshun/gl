#include "collision.h"
#include <glm/common.hpp>

GLchar seCollisionRectInit(seCollisionRectCreateInfo * r)
{
	return 0;
}
GLchar seCollisionCircleInit(seCollisionCircleCreateInfo * c)
{
	return 0;
}
GLchar seCollisionPointInit(seCollisionPointCreateInfo * p)
{
	return 0;
}


GLchar seRRColisionDetect(
		seCollisionRectCreateInfo * r1, 
		seCollisionRectCreateInfo * r2)
{
	/*
	 * return 
	 *	(a.minX <= b.maxX && a.maxX >= b.minX) && 
	 *	(a.minY <= b.maxY && a.maxY >= b.minY) && 
	 *	(a.minZ <= b.maxZ && a.maxZ >= b.minZ);
	*/

	r1->state = 0;
	r2->state = 0;
	if(	
		glm::min(r1->x0, r1->x1) < glm::max(r2->x0, r2->x1) &&
		glm::max(r1->x0, r1->x1) > glm::min(r2->x0, r2->x1) &&
		glm::min(r1->y0, r1->y1) < glm::max(r2->y0, r2->y1) &&
		glm::max(r1->y0, r1->y1) > glm::min(r2->y0, r2->y1) &&
		glm::min(r1->z0, r1->z1) < glm::max(r2->z0, r2->z1) &&
		glm::max(r1->z0, r1->z1) > glm::min(r2->z0, r2->z1)
		)
	{
		r1->state = 1;
		r2->state = 1;
	}
	return 0;
}

GLchar seCCColisionDetect(seCollisionCircleCreateInfo * c1, seCollisionCircleCreateInfo * c2)
{
	GLfloat lengthBetweenCenters =	sqrtf(	(c2->x - c1->x) * (c2->x - c1->x) +
											(c2->y - c1->y) * (c2->y - c1->y) +
											(c2->z - c1->z) * (c2->z - c1->z));

	c1->state = 0;
	c2->state = 0;
	if(lengthBetweenCenters < (c1->radius + c2->radius))
	{
		c1->state = 2;
		c2->state = 2;
	}
	return 0;
}

GLchar seRPCollisionDetect(seCollisionRectCreateInfo * r, seCollisionPointCreateInfo * p)
{
	r->state = 0;
	p->state = 0;
	if(	glm::max(r->x0, r->x1) > p->x &&
		glm::min(r->x0, r->x1) < p->x &&
		glm::max(r->y0, r->y1) > p->y &&
		glm::min(r->y0, r->y1) < p->y &&
		glm::max(r->z0, r->z1) > p->z &&
		glm::min(r->z0, r->z1) < p->z)
	{
		r->state = 3;
		p->state = 1;
	}
	return 0;
}

GLchar seCPCollisionDetect(seCollisionCircleCreateInfo * c, seCollisionPointCreateInfo * p)
{
	c->state = 0;
	p->state = 0;
	GLfloat lengthBetweenCenterAndPoint = sqrtf((c->x - p->x) * (c->x - p->x) +
												(c->y - p->y) * (c->y - p->y) +
												(c->z - p->z) * (c->z - p->z));

	if(lengthBetweenCenterAndPoint  < (c->radius))
	{
		c->state = 3;
		p->state = 2;
	}
	return 0;
}
