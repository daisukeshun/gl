#include "matrix.h"


/*
 * 0, 1, 2, 3
 * 4, 5, 6, 7,
 * 8, 9, 10, 11,
 * 12, 13, 14, 15
 */


///////////////////////////////////////////////////////////////////////////////
// return a perspective frustum with 6 params similar to glFrustum()
// (left, right, bottom, top, near, far)
///////////////////////////////////////////////////////////////////////////////
float * setFrustum(float l, float r, float b, float t, float n, float f)
{
    float * matrix = (float*)calloc(16, sizeof(float));

    matrix[0]  =  2 * n / (r - l);
    matrix[5]  =  2 * n / (t - b);
    matrix[8]  =  (r + l) / (r - l);
    matrix[9]  =  (t + b) / (t - b);
    matrix[10] = -(f + n) / (f - n);
    matrix[11] = -1;
    matrix[14] = -(2 * f * n) / (f - n);
    matrix[15] =  0;
	/*
    matrix[0]  =  2 * n / (r - l);
    matrix[2]  =  (r + l) / (r - l);
    matrix[5]  =  2 * n / (t - b);
    matrix[6]  =  (t + b) / (t - b);
    matrix[10] = -(f + n) / (f - n);
    matrix[11] = -(2 * f * n) / (f - n);
    matrix[14] = -1;
    matrix[15] =  0;
	*/
	return matrix;
}

///////////////////////////////////////////////////////////////////////////////
// return a symmetric perspective frustum with 4 params similar to
// gluPerspective() (vertical field of view, aspect ratio, near, far)
///////////////////////////////////////////////////////////////////////////////
float * setPerspective(float fovY, float aspectRatio, float front, float back)
{
    float tangent = tanf(fovY/2 * DEG2RAD);   // tangent of half fovY
    float height = front * tangent;           // half height of near plane
    float width = height * aspectRatio;       // half width of near plane

    // params: left, right, bottom, top, near, far
    return setFrustum(-width, width, -height, height, front, back);
}

///////////////////////////////////////////////////////////////////////////////
// set a orthographic frustum with 6 params similar to glOrtho()
// (left, right, bottom, top, near, far)
///////////////////////////////////////////////////////////////////////////////
float * setOrthoFrustum(float l, float r, float b, float t, float n, float f)
{
    float * matrix = (float*)calloc(16, sizeof(float));
    matrix[0]  =  2 / (r - l);
    matrix[5]  =  2 / (t - b);
    matrix[10] = -2 / (f - n);
    matrix[12] = -(r + l) / (r - l);
    matrix[13] = -(t + b) / (t - b);
    matrix[14] = -(f + n) / (f - n);
    return matrix;
}

void matrix_print(float * matrix)
{
	for(int i = 0; i < 16; i++)
	{
		i % 4 == 0 ? printf("\n") : 0;
		printf("%f ", matrix[i]);
	}
	printf("\n");
}

float * setTranslate(float x, float y, float z)
{
    float * matrix = (float*)calloc(16, sizeof(float));
    matrix[0]  = 1;
    matrix[5]  = 1;
    matrix[10] = 1;
    matrix[15] = 1;

    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
    return matrix;
}

float * setScale(float x, float y, float z)
{
    float * matrix = (float*)calloc(16, sizeof(float));
    matrix[0]  = x;
    matrix[5]  = y;
    matrix[10] = z;
    matrix[15] = 1;
    return matrix;
}

float * setIdentity(void)
{
	return setTranslate(0, 0, 0);
}
