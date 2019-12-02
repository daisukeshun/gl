#pragma once
#include <string.h>
#include "types.h"
#include "mesh.h"

//functions for free memory of 2-dimensional arrays


// mesh loading (hm... yes, it's obvious)
void loadMesh(Mesh * result, const char* path)
{

	FILE* object = NULL;
	object = fopen(path, "r");
	if(object == NULL){
		printf("ERROR!!!! \n");
		printf("can't load file %s\n", path);
		printf("ERROR!!!! \n");
		exit(1);
	}

	float** temp_v = (float**)calloc(1, sizeof(float*));
	int** temp_f = (int**)calloc(1, sizeof(int*));
	float buf_v[3] = { 0 };
	float buf_vn[3] = { 0 };
	int	buf_f[3] = { 0 };
	int	buf_fn[3] = { 0 };
	int v, vn, f;
	v = vn = f = 1;
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
			else if (strcmp(lineHeader, "f") == 0)
			{

				fscanf(object, "%d/%d %d/%d %d/%d\n",
					&buf_f[0], &buf_fn[0],
					&buf_f[1], &buf_fn[1],
					&buf_f[2], &buf_fn[2]);
				// ADD buf_f in temp_f
				temp_f[f - 1] = (int*)calloc(3, sizeof(int));
				temp_f[f - 1][0] = buf_f[0];
				temp_f[f - 1][1] = buf_f[1];
				temp_f[f - 1][2] = buf_f[2];

				f++;
				temp_f = (int**)realloc(temp_f, sizeof(int*) * f);
			}

		}

	}

	printf("%d\n", f);

	result->polNum = f - 1;
	result->polygons = (Triangle4f*)calloc(result->polNum,  sizeof(Triangle4f));
	isVec3f(result->position);
	isVec3f(result->rotation);
	printf("%d\n", f);
	for(int i = 0; i < (int)result->polNum; i++){
		isTriangle4f(result->polygons[i]);
	}

	float len = 0, len2;
	for (int i = 0; i < f - 1; i++)
	{
		for(int j = 0; j < 3; j++){
			for(int k = 0; k < 3; k++){
				result->polygons[i][j][k] = temp_v[temp_f[i][j]-1][k];
			}
			len2 = sqrtf(
						result->polygons[i][j][0]*result->polygons[i][j][0] +
						result->polygons[i][j][0]*result->polygons[i][j][0] +
						result->polygons[i][j][0]*result->polygons[i][j][0]);
			if(len < len2){
				len = len2;
			}

		}
	}
	printf("len:%f\n", len);

	for (int i = 0; i < f - 1; i++)
	{
		for(int j = 0; j < 3; j++){
			for(int k = 0; k < 3; k++){
				result->polygons[i][j][k] /= len;
			}
		}
	}
	for(int i = 0; i < (f - 1); i++){
		free(temp_f[i]);
	}
	for(int i = 0; i < (v - 1); i++){
		free(temp_v[i]);
	}
	printf("bufs was deleted\n");
	fclose(object);
}

