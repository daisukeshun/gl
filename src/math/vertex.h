#include <GL/gl.h>

typedef struct Vertex
{
	GLfloat vector[3];
	GLfloat color[4];
	//GLfloat texture[2];
	//GLuint textureID;
} Vertex;


void setVector2f(GLfloat * vector, GLfloat x, GLfloat y);
void setVector3f(GLfloat * vector, GLfloat x, GLfloat y, GLfloat z);
void setVector4f(GLfloat * vector, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
