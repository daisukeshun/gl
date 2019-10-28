#pragma once
#include <string.h>
#include "types.h"
#include "mesh.h"

//functions for free memory of 2-dimensional arrays


// mesh loading (hm... yes, it's obvious)
void loadMesh(Mesh * result, const char* path)
{

	FILE* object = NULL;

	float** temp_v = (float**)calloc(1, sizeof(float*));
	float** temp_vn = (float**)calloc(1, sizeof(float*));
	int** temp_f = (int**)calloc(1, sizeof(int*));
	int** temp_fn = (int**)calloc(1, sizeof(int*));
	float buf_v[3] = { 0 };
	float buf_vn[3] = { 0 };
	int	buf_f[3] = { 0 };
	int	buf_fn[3] = { 0 };
	int v, vn, f;
	v = vn = f = 1;
	object = fopen(path, "r");
	char lineHeader[128];
	int res;
	while (1)
	{
		res = fscanf(object, "%s", lineHeader);
		if (res == EOF)
		{
			break;
		}
		else
		{
			if (strcmp(lineHeader, "v") == 0)
			{

				fscanf(object, "%f %f %f\n", &buf_v[0], &buf_v[1], &buf_v[2]);
				//// ADD buf_v in temp_v
				temp_v[v - 1] = (float*)calloc(3, sizeof(float));
				temp_v[v - 1][0] = buf_v[0];
				temp_v[v - 1][1] = buf_v[1];
				temp_v[v - 1][2] = buf_v[2];
				v++;
				temp_v = (float**)realloc(temp_v, sizeof(float*) * v);
				/*printf("%f %f %f\n",
					temp_v[v - 2][0],
					temp_v[v - 2][1], 
					temp_v[v - 2][2]);*/
			}
			else if (strcmp(lineHeader, "vn") == 0)
			{
				fscanf(object, "%f %f %f\n", &buf_vn[0], &buf_vn[1], &buf_vn[2]);
				// ADD buf_vn in temp_vn
				temp_vn[vn - 1] = (float*)calloc(3, sizeof(float));
				temp_vn[vn - 1][0] = buf_vn[0];
				temp_vn[vn - 1][1] = buf_vn[1];
				temp_vn[vn - 1][2] = buf_vn[2];
				vn++;
				temp_vn = (float**)realloc(temp_vn, sizeof(float*) * vn);
			}
			else if (strcmp(lineHeader, "f") == 0)
			{

				fscanf(object, "%d//%d %d//%d %d//%d\n",
					&buf_f[0], &buf_fn[0],
					&buf_f[1], &buf_fn[1],
					&buf_f[2], &buf_fn[2]);
				// ADD buf_f in temp_f
				temp_f[f - 1] = (int*)calloc(3, sizeof(int));
				temp_f[f - 1][0] = buf_f[0];
				temp_f[f - 1][1] = buf_f[1];
				temp_f[f - 1][2] = buf_f[2];

				temp_fn[f - 1] = (int*)calloc(3, sizeof(int));
				temp_fn[f - 1][0] = buf_fn[0];
				temp_fn[f - 1][1] = buf_fn[1];
				temp_fn[f - 1][2] = buf_fn[2];

				f++;
				temp_f = (int**)realloc(temp_f, sizeof(int*) * f);
				temp_fn = (int**)realloc(temp_fn, sizeof(int*) * f);

			}

		}

	}

	result->polNum = f - 1;
	result->normals = (vec3f*)calloc(result->polNum, sizeof(vec3f));
	result->polygons = (Triangle4f*)calloc(result->polNum,  sizeof(Triangle4f));
	isVec3f(result->position);
	isVec3f(result->rotation);
	for(int i = 0; i < f - 1; i++){
		isTriangle4f(result->polygons[i]);
		isVec4f(result->normals[i]);
	}

	for (int i = 0; i < (int)result->polNum; i++)
	{
		result->polygons[i][0][0] = temp_v[temp_f[i][0]-1][0];
		result->polygons[i][0][1] = temp_v[temp_f[i][0]-1][1];
		result->polygons[i][0][2] = temp_v[temp_f[i][0]-1][2];
		
		result->polygons[i][1][0] = temp_v[temp_f[i][1]-1][0];
		result->polygons[i][1][1] = temp_v[temp_f[i][1]-1][1];
		result->polygons[i][1][2] = temp_v[temp_f[i][1]-1][2];
		
		result->polygons[i][2][0] = temp_v[temp_f[i][2]-1][0];
		result->polygons[i][2][1] = temp_v[temp_f[i][2]-1][1];
		result->polygons[i][2][2] = temp_v[temp_f[i][2]-1][2];

		result->normals[i][0] = temp_vn[temp_fn[i][0] - 1][0];
		result->normals[i][1] = temp_vn[temp_fn[i][0] - 1][1];
		result->normals[i][2] = temp_vn[temp_fn[i][0] - 1][2];
	}

	for(int i = 0; i < (f - 1); i++){
		free(temp_f[i]);
		free(temp_fn[i]);
	}
	for(int i = 0; i < (v - 1); i++){
		free(temp_v[i]);
	}
	for(int i = 0; i < (vn - 1); i++){
		free(temp_vn[i]);
	}
	printf("bufs was deleted\n");
	fclose(object);
}

