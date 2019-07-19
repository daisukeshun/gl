#pragma once
#include "constants.h"
#define uint unsigned int;
//ver. 2.0

// matrix

typedef float** fMatrix;
typedef int** iMatrix;
// For points I will use arrays of integers;

typedef float* Point2d;
typedef float* Point3d;

// Triangle is array [3][X], where X is count of coordinates in point (3 or 2)

typedef float** Triangle2d;
typedef float** Triangle3d;
typedef float* Normal;

//Course my mesh is array of triangles

typedef Triangle3d* Polygons;
typedef Normal* Normals;

typedef struct
{
	Normals normals;
	Polygons polygons;
	int pNum;
} Mesh;
// Init of triangles, points and meshes (i'm so lazy for writing this things many times)

#define defPoint2d(Point) Point2d Point = (Point2d)calloc(2, sizeof(float));
#define defPoint3d(Point) Point3d Point = (Point3d)calloc(3, sizeof(float));

#define defTriangle2d(Triangle) Triangle2d Triangle = (Triangle2d)calloc(3, sizeof(Point2d));
#define defTriangle3d(Triangle) Triangle3d Triangle = (Triangle3d)calloc(3, sizeof(Point3d));
#define defNormal(normal) Normal normal = (Normal)calloc(3, sizeof(float));

#define isPoint2d(Point) Point = (Point2d)calloc(2, sizeof(float));
#define isPoint3d(Point) Point = (Point3d)calloc(3, sizeof(float));
#define isNormal(normal) normal = (Normal)calloc(3, sizeof(float));

#define defPolygons(polygons, count) Triangle3d* polygons = (Triangle3d*)calloc(count, sizeof(Triangle3d));
#define defNormals(normals, count) Normal* normals = (Normal*)calloc(count, sizeof(Normal));

#define deffMatrix4x4(matrix) fMatrix matrix = (fMatrix)calloc(4, sizeof(float*));
#define isfMatrix4x4(matrix)  matrix = (fMatrix)calloc(4, sizeof(float*));

#define defiMatrix4x4(matrix) iMatrix matrix = (iMatrix)calloc(4, sizeof(int*));
#define isiMatrix4x4(matrix)  matrix = (iMatrix)calloc(4, sizeof(int*));

#define deffMatrix3x3(matrix) fMatrix matrix = (fMatrix)calloc(3, sizeof(float*));
#define isfMatrix3x3(matrix)  matrix = (fMatrix)calloc(3, sizeof(float*));

#define defiMatrix3x3(matrix) iMatrix matrix = (iMatrix)calloc(3, sizeof(int*));
#define isiMatrix3x3(matrix)  matrix = (iMatrix)calloc(3, sizeof(int*));

// No comments

Triangle2d createTriangle2d(void) {
	defTriangle2d(result);

	isPoint2d(result[0]);
	isPoint2d(result[1]);
	isPoint2d(result[2]);

	return result;
}

Triangle3d createTriangle3d(void) {
	defTriangle2d(result);

	isPoint3d(result[0]);
	isPoint3d(result[1]);
	isPoint3d(result[2]);

	return result;
}

// Common drawing of triangle

void drawTriangle2d(SDL_Renderer* renderer, const Triangle2d triangle) {

	SDL_RenderDrawLine(renderer, triangle[0][0], triangle[0][1], triangle[1][0], triangle[1][1]);
	SDL_RenderDrawLine(renderer, triangle[1][0], triangle[1][1], triangle[2][0], triangle[2][1]);
	SDL_RenderDrawLine(renderer, triangle[2][0], triangle[2][1], triangle[0][0], triangle[0][1]);

}

// Creation of mesh

Polygons createPolygons(const int polygons) {
	defPolygons(result, polygons);
	for (int i = 0; i < polygons; i++)
	{
		result[i] = createTriangle3d();
	}
	return result;
}

float** createNormals(const int normals) {
	float** result = (float**)calloc(normals, sizeof(float*));
	for (int i = 0; i < normals; i++)
	{
		result[i] = (float*)calloc(3, sizeof(float));
	}
}

// generates rotation matrices

fMatrix createRotationX(fMatrix result, const float angle) {

	result[0][0] = 1;
	result[1][1] = cos(angle * M_PI / 180);
	result[2][2] = cos(angle * M_PI / 180);
	result[1][2] = -sin(angle * M_PI / 180);
	result[2][1] = sin(angle * M_PI / 180);

	return result;
}

fMatrix createRotationY(fMatrix result, const float angle) {

	result[0][0] = cos(angle * M_PI / 180);
	result[0][2] = sin(angle * M_PI / 180);
	result[1][1] = 1;
	result[2][0] = -sin(angle * M_PI / 180);
	result[2][2] = cos(angle * M_PI / 180);

	return result;
}

fMatrix createRotationZ(fMatrix result, const float angle) {

	result[0][0] = cos(angle * M_PI / 180);
	result[1][1] = cos(angle * M_PI / 180);
	result[0][1] = -sin(angle * M_PI / 180);
	result[1][0] = sin(angle * M_PI / 180);
	result[2][2] = 1;

	return result;
}

// Multiply our matricses

Point3d rotatePoint(Point3d result, const fMatrix rotationMatrix, Point3d point) {

	result[0] = rotationMatrix[0][0] * point[0] + rotationMatrix[0][1] * point[1] + rotationMatrix[0][2] * point[2];
	result[1] = rotationMatrix[1][0] * point[0] + rotationMatrix[1][1] * point[1] + rotationMatrix[1][2] * point[2];
	result[2] = rotationMatrix[2][0] * point[0] + rotationMatrix[2][1] * point[1] + rotationMatrix[2][2] * point[2];

	return result;
}

Triangle3d rotateTriangle(Triangle3d result, const fMatrix rotationMatrix, Triangle3d triangle) {

	rotatePoint(result[0], rotationMatrix, triangle[0]);
	rotatePoint(result[1], rotationMatrix, triangle[1]);
	rotatePoint(result[2], rotationMatrix, triangle[2]);
	return result;
}

// Convert 3d polygon to 2d projection

Triangle2d toTriangle2d(Triangle2d result, Triangle3d triangle) {

	switch ((int)(triangle[0][2] * 1000))
	{
	case 0:
		result[0][0] = triangle[0][0] / zx;
		result[0][1] = triangle[0][1] / zy;
		break;
	default:
		result[0][0] = triangle[0][0] / (triangle[0][2] + zx);
		result[0][1] = triangle[0][1] / (triangle[0][2] + zy);
		break;
	}

	switch ((int)(triangle[1][2] * 1000))
	{
	case 0:
		result[1][0] = triangle[1][0] / zx;
		result[1][1] = triangle[1][1] / zy;
		break;
	default:
		result[1][0] = triangle[1][0] / (triangle[1][2] + zx);
		result[1][1] = triangle[1][1] / (triangle[1][2] + zy);
		break;
	}
	switch ((int)(triangle[2][2] * 1000))
	{
	case 0:
		result[2][0] = triangle[2][0] / zx;
		result[2][1] = triangle[2][1] / zy;
		break;
	default:
		result[2][0] = triangle[2][0] / (triangle[2][2] + zx);
		result[2][1] = triangle[2][1] / (triangle[2][2] + zy);
		break;
	}


	result[0][0] /= aspectRatio;
	//result[0][1] *= aspectRatio;

	result[1][0] /= aspectRatio;
	//result[1][1] *= aspectRatio;

	result[2][0] /= aspectRatio;
	//result[2][1] *= aspectRatio;


	result[0][0]++;
	result[0][1]++;
	result[1][0]++;
	result[1][1]++;
	result[2][0]++;
	result[2][1]++;



	result[0][0] = result[0][0] * 0.5 * WINDOW_WIDTH;
	result[0][1] = result[0][1] * 0.5 * WINDOW_HEIGHT;
	result[1][0] = result[1][0] * 0.5 * WINDOW_WIDTH;
	result[1][1] = result[1][1] * 0.5 * WINDOW_HEIGHT;
	result[2][0] = result[2][0] * 0.5 * WINDOW_WIDTH;
	result[2][1] = result[2][1] * 0.5 * WINDOW_HEIGHT;



	return result;
}