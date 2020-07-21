#include <math.h>
#include <malloc.h>

#define DEG2RAD 0.0174533f

float * setFrustum(float l, float r, float b, float t, float n, float f);
float * setPerspective(float fovY, float aspectRatio, float front, float back);
float * setOrthoFrustum(float l, float r, float b, float t, float n, float f);
float * setTranslate(float x, float y, float z);
float * setScale(float x, float y, float z);
float * setIdentity(void);
void glhFrustumf2(float *matrix, float left, float right, float bottom, float top, float znear, float zfar);
void glhPerspectivef2(float *matrix, float fovyInDegrees, float aspectRatio, float znear, float zfar);

void matrix_print(float * matrix);
