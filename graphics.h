#pragma once
#include "camera.h"
#include "types.h"
#include "settings.h"
#include <math.h>
#include <malloc.h>

#define M_PI 3.141592 // my redefined PI

//____________________________definition start____________________________
//float vectors 
#define defVec4f(vector) vec4f vector = (vec4f)calloc(4, sizeof(float)); vector[3] = 1;
#define defVec3f(vector) vec3f vector = (vec3f)calloc(3, sizeof(float));
#define defVec2f(vector) vec2f vector = (vec2f)calloc(2, sizeof(float));

#define isVec4f(vector)	vector = (vec4f)calloc(4, sizeof(float)); vector[3] = 1;
#define isVec3f(vector)	vector = (vec3f)calloc(3, sizeof(float));
#define isVec2f(vector)	vector = (vec2f)calloc(2, sizeof(float));

//int vectors
#define defVec4i(vector) vec4i vector = (vec4i)calloc(4, sizeof(int)); vector[3] = 1;
#define defVec3i(vector) vec3i vector = (vec3i)calloc(3, sizeof(int));
#define defVec2i(vector) vec2i vector = (vec2i)calloc(2, sizeof(int));

#define isVec4i(vector)	vector = (vec4i)calloc(4, sizeof(int)); vector[3] = 1; 
#define isVec3i(vector)	vector = (vec3i)calloc(3, sizeof(int));
#define isVec2i(vector)	vector = (vec2i)calloc(2, sizeof(int));

//delete vectors
#define delVec(vector) free(vector);

//float matrices
#define defMat4f(matrix) mat4f matrix = (mat4f)calloc(4, sizeof(mat4f));\
										matrix[0] = (vec4f)calloc(4, sizeof(float));\
										matrix[1] = (vec4f)calloc(4, sizeof(float));\
										matrix[2] = (vec4f)calloc(4, sizeof(float));\
										matrix[3] = (vec4f)calloc(4, sizeof(float));

#define defMat3f(matrix) mat3f matrix = (mat3f)calloc(3, sizeof(mat3f));\
										matrix[0] = (vec3f)calloc(3, sizeof(float));\
										matrix[1] = (vec3f)calloc(3, sizeof(float));\
										matrix[2] = (vec3f)calloc(3, sizeof(float));

#define defMat2f(matrix) mat2f matrix = (mat2f)calloc(2, sizeof(mat2f));\
										matrix[0] = (vec2f)calloc(2, sizeof(float));\
										matrix[1] = (vec2f)calloc(2, sizeof(float));\

//int matrix
#define defMat4i(matrix) mat4i matrix = (mat4i)calloc(4, sizeof(mat4i));\
										matrix[0] = (vec4f)calloc(4, sizeof(int));\
										matrix[1] = (vec4f)calloc(4, sizeof(int));\
										matrix[2] = (vec4f)calloc(4, sizeof(int));\
										matrix[3] = (vec4f)calloc(4, sizeof(int));

#define defMat3i(matrix) mat3i matrix = (mat3i)calloc(3, sizeof(mat3i));\
										matrix[0] = (vec3f)calloc(3, sizeof(int));\
										matrix[1] = (vec3f)calloc(3, sizeof(int));\
										matrix[2] = (vec3f)calloc(3, sizeof(int));

#define defMat2i(matrix) mat2i matrix = (mat2i)calloc(2, sizeof(mat2i));\
										matrix[0] = (vec2f)calloc(2, sizeof(int));\
										matrix[1] = (vec2f)calloc(2, sizeof(int));\

//____________________________definition end_______________________________________

//____________________________delete our matrices__________________________________
#define delMat4(matrix) free(matrix[0]);\
						free(matrix[1]);\
						free(matrix[2]);\
						free(matrix[3]);\
						free(matrix)

#define delMat3(matrix) free(matrix[0]);\
						free(matrix[1]);\
						free(matrix[2]);\
						free(matrix)

#define delMat2(matrix) free(matrix[0]);\
						free(matrix[1]);\
						free(matrix)
//_______________________________end of deleting___________________________________
//
//____________________________setters for vectors__________________________________
//all of this setters can work with any type of vectors (int, float)
#define setVec4(vector, x, y, z, w) vector[0] = x;\
									vector[1] = y;\
									vector[2] = z;\
									vector[3] = w;

#define setVec3(vector, x, y, z)	vector[0] = x;\
									vector[1] = y;\
									vector[2] = z;

#define setVec2(vector, x, y)		vector[0] = x;\
									vector[1] = y;

//_______________________________end of setters_____________________________________

//____________________________setters for matrices__________________________________
//all of this setters can work with any type of matrices (int, float)
#define setMat4(matrix, vec1, vec2, vec3, vec4) setVec4(matrix[0], vec1);\
												setVec4(matrix[1], vec2);\
												setVec4(matrix[2], vec3);\
												setVec4(matrix[3], vec4);

#define setMat3(matrix, vec1, vec2, vec3)		setVec4(matrix[0], vec1);\
												setVec4(matrix[1], vec2);\
												setVec4(matrix[2], vec3); 

#define setMat2(matrix, vec1, vec2, vec3)		setVec4(matrix[0], vec1);\
												setVec4(matrix[1], vec2);
//__________________________________end of setters__________________________________

//__________________________________matrix multiplying______________________________
//vectors must be same type with matrices
void matMul4f(vec4f ret, const mat4f mat, vec4f src){
	ret[0] = mat[0][0] * src[0] + mat[0][1] * src[1] + mat[0][2] * src[2] + mat[0][3] * src[3];
	ret[1] = mat[1][0] * src[0] + mat[1][1] * src[1] + mat[1][2] * src[2] + mat[1][3] * src[3];
	ret[2] = mat[2][0] * src[0] + mat[2][1] * src[1] + mat[2][2] * src[2] + mat[2][3] * src[3];
	ret[3] = mat[3][0] * src[0] + mat[3][1] * src[1] + mat[3][2] * src[2] + mat[3][3] * src[3];
	
	if (ret[3] != 1) { 
        ret[0] /= ret[3]; 
        ret[1] /= ret[3]; 
        ret[2] /= ret[3]; 
    } 
}

void matMul3f(vec3f ret, const mat3f mat, vec3f src){
	ret[0] = mat[0][0] * src[0] + mat[0][1] * src[1] + mat[0][2] * src[2];
	ret[1] = mat[1][0] * src[0] + mat[1][1] * src[1] + mat[1][2] * src[2];
	ret[2] = mat[2][0] * src[0] + mat[2][1] * src[1] + mat[2][2] * src[2];
}

void matMul2f(vec2f ret, const mat2f mat, vec2f src){
	ret[0] = mat[0][0] * src[0] + mat[0][1] * src[1];
	ret[1] = mat[1][0] * src[0] + mat[1][1] * src[1];
}

void matMul4i(vec4i ret, const mat4i mat, vec4i src){
	ret[0] = mat[0][0] * src[0] + mat[0][1] * src[1] + mat[0][2] * src[2] + mat[0][3] * src[3];
	ret[1] = mat[1][0] * src[0] + mat[1][1] * src[1] + mat[1][2] * src[2] + mat[1][3] * src[3];
	ret[2] = mat[2][0] * src[0] + mat[2][1] * src[1] + mat[2][2] * src[2] + mat[2][3] * src[3];
	ret[3] = mat[3][0] * src[0] + mat[3][1] * src[1] + mat[3][2] * src[2] + mat[3][3] * src[3];

	if (ret[3] != 1) { 
        ret[0] /= ret[3]; 
        ret[1] /= ret[3]; 
        ret[2] /= ret[3]; 
    } 
	
}

void matMul3i(vec3i ret, const mat3i mat, vec3i src){
	ret[0] = mat[0][0] * src[0] + mat[0][1] * src[1] + mat[0][2] * src[2];
	ret[1] = mat[1][0] * src[0] + mat[1][1] * src[1] + mat[1][2] * src[2];
	ret[2] = mat[2][0] * src[0] + mat[2][1] * src[1] + mat[2][2] * src[2];
}

void matMul2i(vec2i ret, const mat2i mat, vec2i src){
	ret[0] = mat[0][0] * src[0] + mat[0][1] * src[1];
	ret[1] = mat[1][0] * src[0] + mat[1][1] * src[1];
}
//__________________________________matrix multiplying end__________________________

//__________________________________vector adding___________________________________

void add4f(vec4f ret, vec4f a, vec4f b){
	setVec4(ret,
			a[0] + b[0],
			a[1] + b[1],
			a[2] + b[2],
			a[3] + b[3]);
}

void add3f(vec3f ret, vec3f a, vec3f b){
	setVec3(ret,
			a[0] + b[0],
			a[1] + b[1],
			a[2] + b[2]);
}

void add2f(vec2f ret, vec2f a, vec2f b){
	setVec2(ret,
			a[0] + b[0],
			a[1] + b[1]);
}
void add4i(vec4i ret, vec4i a, vec4i b){
	setVec4(ret,
			a[0] + b[0],
			a[1] + b[1],
			a[2] + b[2],
			a[3] + b[3]);
}

void add3i(vec3i ret, vec3i a, vec3i b){
	setVec3(ret,
			a[0] + b[0],
			a[1] + b[1],
			a[2] + b[2]);
}

void add2i(vec2i ret, vec2i a, vec2i b){
	setVec2(ret,
			a[0] + b[0],
			a[1] + b[1]);
}
void sub4f(vec4f ret, vec4f a, vec4f b){
	setVec4(ret,
			a[0] + b[0],
			a[1] + b[1],
			a[2] + b[2],
			a[3] + b[3]);
}

void sub3f(vec3f ret, vec3f a, vec3f b){
	setVec3(ret,
			a[0] + b[0],
			a[1] + b[1],
			a[2] + b[2]);
}

void sub2f(vec2f ret, vec2f a, vec2f b){
	setVec2(ret,
			a[0] + b[0],
			a[1] + b[1]);
}
void sub4i(vec4i ret, vec4i a, vec4i b){
	setVec4(ret,
			a[0] + b[0],
			a[1] + b[1],
			a[2] + b[2],
			a[3] + b[3]);
}

void sub3i(vec3i ret, vec3i a, vec3i b){
	setVec3(ret,
			a[0] + b[0],
			a[1] + b[1],
			a[2] + b[2]);
}

void sub2i(vec2i ret, vec2i a, vec2i b){
	setVec2(ret,
			a[0] + b[0],
			a[1] + b[1]);
}
//__________________________________end of adding___________________________________
//__________________________________dot products____________________________________
//vectors must be same type
void dot4f(vec4f ret, vec4f src){
	ret[0] *= src[0];
	ret[1] *= src[0];
	ret[2] *= src[0];
	ret[3] *= src[0];
}

void dot3f(vec3f ret, vec3f src){
	ret[0] *= src[0];
	ret[1] *= src[0];
	ret[2] *= src[0];
}

void dot2f(vec2f ret, vec2f src){
	ret[0] *= src[0];
	ret[1] *= src[0];
}

void dot4i(vec4i ret, vec4i src){
	ret[0] *= src[0];
	ret[1] *= src[0];
	ret[2] *= src[0];
	ret[3] *= src[0];
}

void dot3i(vec3i ret, vec3i src){
	ret[0] *= src[0];
	ret[1] *= src[0];
	ret[2] *= src[0];
}

void dot2i(vec2i ret, vec2i src){
	ret[0] *= src[0];
	ret[1] *= src[0];
}
//__________________________________dot products end________________________________


//__________________________________cross products _________________________________
void cross4f(vec4f ret, vec4f a, vec4f b){
	ret[0] = a[1]*b[2] - a[2]*b[1];
	ret[1] = a[2]*b[0] - a[0]*b[2];
	ret[2] = a[0]*b[1] - a[1]*b[0];
}

void cross3f(vec3f ret, vec3f a, vec3f b){
	ret[0] = a[1]*b[2] - a[2]*b[1];
	ret[1] = a[2]*b[0] - a[0]*b[2];
	ret[2] = a[0]*b[1] - a[1]*b[0];
}

void cross4i(vec4i ret, vec4i a, vec4i b){
	ret[0] = a[1]*b[2] - a[2]*b[1];
	ret[1] = a[2]*b[0] - a[0]*b[2];
	ret[2] = a[0]*b[1] - a[1]*b[0];
}

void cross3i(vec3i ret, vec3i a, vec3i b){
	ret[0] = a[1]*b[2] - a[2]*b[1];
	ret[1] = a[2]*b[0] - a[0]*b[2];
	ret[2] = a[0]*b[1] - a[1]*b[0];
}
//__________________________________cross products end______________________________

//__________________________________matrix generations______________________________
void createRotationX(mat4f ret, const float angle) {
	ret[0][0] = 1;
	ret[1][1] = cos(angle * M_PI / 180); ret[1][2] = -sin(angle * M_PI / 180);
	ret[2][1] = sin(angle * M_PI / 180); ret[2][2] = cos(angle * M_PI / 180);
	ret[3][3] = 1;
}

void createRotationY(mat4f ret, const float angle) {
	ret[0][0] = cos(angle * M_PI / 180);	ret[0][2] = sin(angle * M_PI / 180);
	ret[1][1] = 1;
	ret[2][0] = -sin(angle * M_PI / 180);	ret[2][2] = cos(angle * M_PI / 180);
	ret[3][3] = 1;
	
}

void createRotationZ(mat4f ret, const float angle) {
	ret[0][0] = cos(angle * M_PI / 180); ret[0][1] = -sin(angle * M_PI / 180);
	ret[1][0] = sin(angle * M_PI / 180); ret[1][1] = cos(angle * M_PI / 180);
	ret[2][2] = 1;
	ret[3][3] = 1;
}

void createTranslation(mat4f ret, const vec4f vec) {
	ret[0][0] = 1; ret[0][3] = vec[0];
	ret[1][1] = 1; ret[1][3] = vec[1];
	ret[2][2] = 1; ret[2][3] = vec[2];
	ret[3][3] = 1;
}

void createInvertTranslation(mat4f ret) {
	ret[0][3] *= -1;
	ret[1][3] *= -1;
	ret[2][3] *= -1;
}

void createScale(mat4f ret, const vec4f vector) {
	ret[0][0] = vector[0];
	ret[1][1] = vector[1];
	ret[2][2] = vector[2];
	ret[3][3] = 1;
}

void createProjectionMatrix(mat4f ret, Camera * camera){
	float scale = 1 / tanf(camera->POV * 0.5 * M_PI / 180); 
    ret[0][0] = scale; // scale the x coordinates of the projected point 
    ret[1][1] = scale; // scale the y coordinates of the projected point 
    ret[2][2] = -(camera->zFar + camera->zNear) / (camera->zFar - camera->zNear);				// used to remap z to [0,1] 
    ret[3][2] = -2*(camera->zFar * camera->zNear) / (camera->zFar - camera->zNear); // used to remap z [0,1] 
    ret[2][3] = -1; // set w = -z 
    ret[3][3] = 0; 
}
//__________________________________genereations end________________________________

#define defTriangle4f(triangle) vec4f * triangle = (vec4f*)calloc(3, sizeof(vec4f));\
										  isVec4f(triangle[0]);\
										  isVec4f(triangle[1]);\
										  isVec4f(triangle[2]);

#define defTriangle2f(triangle) vec2f * triangle = (vec4f*)calloc(2, sizeof(vec4f));\
										  isVec4f(triangle[0]);\
										  isVec4f(triangle[1]);

#define isTriangle4f(triangle) triangle = (vec4f*)calloc(3, sizeof(vec4f));\
										  isVec4f(triangle[0]);\
										  isVec4f(triangle[1]);\
										  isVec4f(triangle[2]);

#define isTriangle2f(triangle) triangle = (vec4f*)calloc(2, sizeof(vec4f));\
										  isVec4f(triangle[0]);\
										  isVec4f(triangle[1]);\
										  isVec4f(triangle[2]);

#define defTriangle4i(triangle) vec4i * triangle = (vec4i*)calloc(3, sizeof(vec4i));\
										  isVec4i(triangle[0]);\
										  isVec4i(triangle[1]);\
										  isVec4i(triangle[2]);

#define defTriangle2i(triangle) vec2i * triangle = (vec2i*)calloc(3, sizeof(vec2i));\
										  isVec2i(triangle[0]);\
										  isVec2i(triangle[1]);\
										  isVec2i(triangle[2]);

#define isTriangle4i(triangle) triangle = (vec4i*)calloc(3, sizeof(vec4i));\
										  isVec4i(triangle[0]);\
										  isVec4i(triangle[1]);\
										  isVec4i(triangle[2]);

#define isTriangle2i(triangle) triangle = (vec2i*)calloc(3, sizeof(vec2i));\
										  isVec2i(triangle[0]);\
										  isVec2i(triangle[1]);

#define delTriangle(triangle)	free(triangle[0]);\
								free(triangle[1]);\
								free(triangle[2]);

#define setTriangle4(triangle, vec1, vec2, vec3)\
	setVec4(triangle[0], vec1[0], vec1[1], vec1[2], vec1[3]);\
	setVec4(triangle[1], vec2[0], vec2[1], vec2[2], vec2[3]);\
	setVec4(triangle[2], vec3[0], vec3[1], vec3[2], vec3[3]);

#define setTriangle3(triangle, vec1, vec2, vec3)\
	setVec4(triangle[0], vec1[0], vec1[1], vec1[2]);\
	setVec4(triangle[1], vec2[0], vec2[1], vec2[2]);\
	setVec4(triangle[2], vec3[0], vec3[1], vec3[2]);

#define setTriangle2(triangle, vec1, vec2, vec3)\
	setVec4(triangle[0], vec1[0], vec1[1]);\
	setVec4(triangle[1], vec2[0], vec2[1]);\
	setVec4(triangle[2], vec3[0], vec3[1]);
