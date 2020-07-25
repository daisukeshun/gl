#include "vertex.h"

void setVector2f(GLfloat * vector, GLfloat x, GLfloat y)
{
	vector[0] = x;
	vector[1] = y;
}
void setVector3f(GLfloat * vector, GLfloat x, GLfloat y, GLfloat z)
{
	vector[0] = x;
	vector[1] = y;
	vector[2] = z;
}
void setVector4f(GLfloat * vector, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	vector[0] = x;
	vector[1] = y;
	vector[2] = z;
	vector[3] = w;
}

