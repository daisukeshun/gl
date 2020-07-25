#include <GL/gl.h>
#include <math.h>
#include <malloc.h>

#define DEG2RAD 0.0174533f

GLfloat * setFrustum( GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GLfloat * setPerspective( GLfloat fovY, GLfloat aspectRatio, GLfloat front, GLfloat back);
GLfloat * setOrthoFrustum(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f);
GLfloat * setTranslate(GLfloat x, GLfloat y, GLfloat z);
GLfloat * setScale( GLfloat x, GLfloat y, GLfloat z);
GLfloat * setRotation( GLfloat x, GLfloat y, GLfloat z);
GLfloat * setIdentity();
GLfloat * glhFrustumf2(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat znear, GLfloat zfar);
GLfloat * glhPerspectivef2(GLfloat fovyInDegrees, GLfloat aspectRatio, GLfloat znear, GLfloat zfar);

void deleteMatrix(GLfloat * matrix);
void matrix_print(GLfloat * matrix);
