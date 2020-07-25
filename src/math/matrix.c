#include "matrix.h"
GLfloat * setFrustum( GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f)
{
    GLfloat * matrix = (GLfloat*)calloc(16, sizeof(GLfloat));
    matrix[0]  =  2 * n / (r - l);
    matrix[5]  =  2 * n / (t - b);
    matrix[8]  =  (r + l) / (r - l);
    matrix[9]  =  (t + b) / (t - b);
    matrix[10] = -(f + n) / (f - n);
    matrix[11] = -1;
    matrix[14] = -(2 * f * n) / (f - n);
    matrix[15] =  0;
	return matrix;
}

GLfloat * setPerspective( GLfloat fovY, GLfloat aspectRatio, GLfloat front, GLfloat back)
{
    GLfloat tangent = tanf(fovY/2 * DEG2RAD);   // tangent of half fovY
    GLfloat height = front * tangent;           // half height of near plane
    GLfloat width = height * aspectRatio;       // half width of near plane

    // params: left, right, bottom, top, near, far
    return setFrustum(-width, width, -height, height, front, back);
}
GLfloat * setOrthoFrustum(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f)
{
    GLfloat * matrix = (GLfloat*)calloc(16, sizeof(GLfloat));
    matrix[0]  =  2 / (r - l);
    matrix[5]  =  2 / (t - b);
    matrix[10] = -2 / (f - n);
    matrix[12] = -(r + l) / (r - l);
    matrix[13] = -(t + b) / (t - b);
    matrix[14] = -(f + n) / (f - n);
	return matrix;
}

GLfloat * setTranslate(GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat *matrix = (GLfloat*)calloc(16, sizeof(GLfloat));
    matrix[0]  = 1;
    matrix[5]  = 1;
    matrix[10] = 1;
    matrix[15] = 1;

    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
	return matrix;
}
GLfloat * setScale( GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat * matrix = (GLfloat*)calloc(16, sizeof(GLfloat));
    matrix[0]  = x;
    matrix[5]  = y;
    matrix[10] = z;
    matrix[15] = 1;
	return matrix;
}

GLfloat * setRotation( GLfloat x, GLfloat y, GLfloat z)
{
    GLfloat * matrix = (GLfloat*)calloc(16, sizeof(GLfloat));
    matrix[0]  = cosf(x*DEG2RAD) * cosf(z*DEG2RAD);
    matrix[1]  = sinf(x*DEG2RAD) * sinf(y*DEG2RAD) * cosf(z*DEG2RAD) + cosf(x*DEG2RAD) * sinf(z*DEG2RAD);
    matrix[2]  = -cosf(x*DEG2RAD) * sinf(y*DEG2RAD) * cosf(z*DEG2RAD) + sinf(x*DEG2RAD) * sinf(z*DEG2RAD);

    matrix[4]  = -cosf(y*DEG2RAD) * sinf(z*DEG2RAD);
    matrix[5]  = -sinf(x*DEG2RAD) * sinf(y*DEG2RAD) * sinf(z*DEG2RAD) + cosf(x*DEG2RAD) * cosf(z*DEG2RAD);
    matrix[6]  = cosf(x*DEG2RAD) * sinf(y*DEG2RAD) * sinf(z*DEG2RAD) + sinf(x*DEG2RAD) * cosf(z*DEG2RAD);

    matrix[8] = sinf(y*DEG2RAD);
    matrix[9] = -sinf(x*DEG2RAD) * cosf(y*DEG2RAD);
    matrix[10] = cosf(x*DEG2RAD) * cosf(y*DEG2RAD);

    matrix[15] = 1;
	return matrix;
}
GLfloat * setIdentity()
{
	return setTranslate(0, 0, 0);
}


void matrix_print(GLfloat * matrix)
{
	for(int i = 0; i < 16; i++)
	{
		i % 4 == 0 ? printf("\n") : 0;
		printf("%f ", matrix[i]);
	}
	printf("\n");
}


void deleteMatrix(GLfloat * matrix)
{
	free(matrix);
	matrix = NULL;
}
