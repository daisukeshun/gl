#pragma once
#ifndef MATHUTIL_H
#define MATHUTIL_H
#include "m_utils.h"
#include <GL/glew.h>

#undef M_PI
#define M_PI 3.14159
#define DEG_TO_RAD 0.0174533
#define RAD_TO_DEG 57.2958
#define degrees(angle) angle * RAD_TO_DEG
#define radians(angle) angle * DEG_TO_RAD

typedef struct MathUtil{

	GLfloat * (*mat4)();
	GLfloat * (*vec3)();
	GLfloat * (*vec4)();

	void (*pMat4)(GLfloat *);
	GLfloat * (*transpose)(GLfloat * M);

	GLfloat * (*perspective)(GLfloat fov,
							 GLfloat aspect,
							 GLfloat znear, 
							 GLfloat zfar);
	GLfloat * (*ortho)(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	GLfloat * (*translation)(GLfloat, GLfloat, GLfloat);
	GLfloat * (*rotation)(GLfloat, GLfloat, GLfloat);
	GLfloat * (*mat4mul)(GLfloat *, GLfloat *);

} MathUtil;

void MathUtil_PrintMatrix(GLfloat * matrix){
	int i, j;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			pFloat(*(matrix + i + 4 * j));
			printf(" ");
		}
		nl;
	}
}

GLfloat * MathUtil_Mat4(){
	GLfloat * ret = (GLfloat*)calloc(16, FSIZE);
	ret[0] = ret[5] = ret[10] = ret[15] = 1.f;
	return ret;
}

GLfloat * MathUtil_Vec4(){
	GLfloat * ret = (GLfloat*)calloc(4, FSIZE);
	return ret;
}

GLfloat * MathUtil_Vec3(){
	GLfloat * ret = (GLfloat *)calloc(3, FSIZE);
	return ret;
}

GLfloat * MathUtil_Ortho(GLfloat left,
						 GLfloat right,
						 GLfloat bottom, 
						 GLfloat top, 
						 GLfloat nearVal, 
						 GLfloat farVal){
	GLfloat * ret = (GLfloat *)calloc(16, FSIZE);
	ret[0]	= 2 / (right - left);
	ret[5]	= 2 / (top - bottom);
	ret[10] = 2 / (farVal - nearVal);

	ret[3]	= - (right + left) / (right - left);
	ret[7]	= - (top + bottom) / (top - bottom);
	ret[11] = - (farVal + nearVal) / (farVal - nearVal);

	ret[14] = 1.f;

	return ret;
}

GLfloat * MathUtil_Projection(GLfloat fov, GLfloat aspect, GLfloat znear, GLfloat zfar){

	GLfloat * ret = (GLfloat *)calloc(16, FSIZE);
	ret[ 0] = (1 / tan(fov / 2)) / aspect;
	ret[ 5] = 1 / tan(fov / 2); 
	ret[10] = (zfar + znear) / (znear - zfar);
   	ret[11] = 2 * zfar * znear / (znear - zfar);
	ret[14] = -1;

	return ret;
}

GLfloat * MathUtil_Rotation(GLfloat x, GLfloat y, GLfloat z){
	GLfloat * M = (GLfloat *)calloc(16, FSIZE);

	const float A = cos(x), B = sin(x), C = cos(y),
              D = sin(y), E = cos(z), F = sin(z);
	const float AD = A * D, BD = B * D;

	M[ 0] = C * E;           M[ 1] = -C * F;          M[ 2] = D;      M[ 3] = 0;
	M[ 4] = BD * E + A * F;  M[ 5] = -BD * F + A * E; M[ 6] = -B * C; M[ 7] = 0;
	M[ 8] = -AD * E + B * F; M[ 9] = AD * F + B * E;  M[10] = A * C;  M[11] = 0;
	M[12] = 0;               M[13] = 0;               M[14] = 0;      M[15] = 1;

	return M;
}

GLfloat * MathUtil_Translation(GLfloat x, GLfloat y, GLfloat z){
	GLfloat * M = (GLfloat *)calloc(16, FSIZE);
	M[ 0] = 1; M[ 1] = 0; M[ 2] = 0; M[ 3] = x;
	M[ 4] = 0; M[ 5] = 1; M[ 6] = 0; M[ 7] = y;
	M[ 8] = 0; M[ 9] = 0; M[10] = 1; M[11] = z;
	M[12] = 0; M[13] = 0; M[14] = 0; M[15] = 1;
	return M;
}

GLfloat * MathUtil_VecMatMul(GLfloat * A, GLfloat * B){
	GLfloat * ret = (GLfloat*)calloc(3, FSIZE);

	return ret;
}

GLfloat * MathUtil_Mat4Mul(GLfloat * A, GLfloat * B){
	GLfloat * M = (GLfloat *)calloc(16, FSIZE);
	M[ 0] = A[ 0] * B[ 0] + A[ 1] * B[ 4] + A[ 2] * B[ 8] + A[ 3] * B[12];
	M[ 1] = A[ 0] * B[ 1] + A[ 1] * B[ 5] + A[ 2] * B[ 9] + A[ 3] * B[13];
	M[ 2] = A[ 0] * B[ 2] + A[ 1] * B[ 6] + A[ 2] * B[10] + A[ 3] * B[14];
	M[ 3] = A[ 0] * B[ 3] + A[ 1] * B[ 7] + A[ 2] * B[11] + A[ 3] * B[15];
	M[ 4] = A[ 4] * B[ 0] + A[ 5] * B[ 4] + A[ 6] * B[ 8] + A[ 7] * B[12];
	M[ 5] = A[ 4] * B[ 1] + A[ 5] * B[ 5] + A[ 6] * B[ 9] + A[ 7] * B[13];
	M[ 6] = A[ 4] * B[ 2] + A[ 5] * B[ 6] + A[ 6] * B[10] + A[ 7] * B[14];
	M[ 7] = A[ 4] * B[ 3] + A[ 5] * B[ 7] + A[ 6] * B[11] + A[ 7] * B[15];
	M[ 8] = A[ 8] * B[ 0] + A[ 9] * B[ 4] + A[10] * B[ 8] + A[11] * B[12];
	M[ 9] = A[ 8] * B[ 1] + A[ 9] * B[ 5] + A[10] * B[ 9] + A[11] * B[13];
	M[10] = A[ 8] * B[ 2] + A[ 9] * B[ 6] + A[10] * B[10] + A[11] * B[14];
	M[11] = A[ 8] * B[ 3] + A[ 9] * B[ 7] + A[10] * B[11] + A[11] * B[15];
	M[12] = A[12] * B[ 0] + A[13] * B[ 4] + A[14] * B[ 8] + A[15] * B[12];
	M[13] = A[12] * B[ 1] + A[13] * B[ 5] + A[14] * B[ 9] + A[15] * B[13];
	M[14] = A[12] * B[ 2] + A[13] * B[ 6] + A[14] * B[10] + A[15] * B[14];
	M[15] = A[12] * B[ 3] + A[13] * B[ 7] + A[14] * B[11] + A[15] * B[15];
	return M;
}

GLfloat * MathUtil_Frustum(float l, float r, float b, float t, float n, float f)
{
    GLfloat * M = (GLfloat *)calloc(16, FSIZE);
    M[0]  = 2 * n / (r - l);
    M[5]  = 2 * n / (t - b);
    M[8]  = (r + l) / (r - l);
    M[9]  = (t + b) / (t - b);
    M[10] = -(f + n) / (f - n);
    M[11] = -1;
    M[14] = -(2 * f * n) / (f - n);
    M[15] = 0;
    return M;
}

GLfloat * MathUtil_AternatePerspective(float fovY, float aspect, float front, float back)
{
    float tangent = tan(radians(fovY/2));	/* tangent of half fovY */
    float height = front * tangent;         /* half height of near plane*/
    float width = height * aspect;          /* half width of near plane*/

    /* params: left, right, bottom, top, near, far*/
    return MathUtil_Frustum(-width, width, -height, height, front, back);
}

GLfloat * MathUtil_TransposeMat4(GLfloat * M){
	GLfloat * ret = (GLfloat *)calloc(16, FSIZE);
	ret[0] = M[0];
	ret[1] = M[4];
	ret[2] = M[8];
	ret[3] = M[12];
	ret[4] = M[1];
	ret[5] = M[5];
	ret[6] = M[9];
	ret[7] = M[13];
	ret[8] = M[2];
	ret[9] = M[6];
	ret[10] = M[10];
	ret[11] = M[14];
	ret[12] = M[3];
	ret[13] = M[7];
	ret[14] = M[11];
	ret[15] = M[15];
	return ret;
}

MathUtil createMathUtil(){
	MathUtil ret;
	ret.mat4 = MathUtil_Mat4;
	ret.vec4 = MathUtil_Vec4;
	ret.vec3 = MathUtil_Vec3;
	ret.pMat4 = MathUtil_PrintMatrix;
	ret.transpose = MathUtil_TransposeMat4;
	ret.perspective = MathUtil_Projection;
	ret.ortho = MathUtil_Ortho;
	ret.rotation = MathUtil_Rotation;
	ret.translation = MathUtil_Translation;
	ret.mat4mul = MathUtil_Mat4Mul;
	return ret;
}

#endif
