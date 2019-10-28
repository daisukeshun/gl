#pragma once
#include "graphics.h"
#include <SDL2/SDL.h>
#include "mesh.h"

void drawTriangle(SDL_Renderer * renderer, Triangle2i triangle);

void drawMesh(SDL_Renderer * renderer, Camera * camera, Mesh * mesh){
	//definition of triangles
	defTriangle4i(buf2);
	defTriangle4f(buf4);

	//rotation matrices (in model coordinates)
	defMat4f(X);
	createRotationX(X, mesh->rotation[0]);
	defMat4f(Y);
	createRotationY(Y, mesh->rotation[1]);
	defMat4f(Z);
	createRotationZ(Z, mesh->rotation[2]);
	
	//translation matrix (in world coordinates)	
	defMat4f(M);
	createTranslation(M, mesh->position);

	//projection matrix 	
	defMat4f(P);
	createProjectionMatrix(P, camera);

	logVec4(P[0]);
	logVec4(P[1]);
	logVec4(P[2]);
	logVec4(P[3]);

	printf("\n");
	for(int i = 0; i < (int)mesh->polNum; i++){
		setTriangle4(buf4,				//copy in buffer polygon
				mesh->polygons[i][0],	//for transform it later
				mesh->polygons[i][1], 
				mesh->polygons[i][2]); 

		matMul4f(buf4[0], Z, buf4[0]);	//project  
		matMul4f(buf4[1], Z, buf4[1]);	//polygon
		matMul4f(buf4[2], Z, buf4[2]);	//on screen

		matMul4f(buf4[0], Y, buf4[0]);	//project  
		matMul4f(buf4[1], Y, buf4[1]);	//polygon
		matMul4f(buf4[2], Y, buf4[2]);	//on screen

		matMul4f(buf4[0], X, buf4[0]);	//project  
		matMul4f(buf4[1], X, buf4[1]);	//polygon
		matMul4f(buf4[2], X, buf4[2]);	//on screen

		matMul4f(buf4[0], M, buf4[0]);	//project  
		matMul4f(buf4[1], M, buf4[1]);	//polygon
		matMul4f(buf4[2], M, buf4[2]);	//on screen
/*
		printf("vector\n");
		logVec4(buf4[0]);
		logVec4(buf4[1]);
		logVec4(buf4[2]);
		printf("\n");
*/
		matMul4f(buf4[0], P, buf4[0]);	//project  
		matMul4f(buf4[1], P, buf4[1]);	//polygon
		matMul4f(buf4[2], P, buf4[2]);	//on screen


		setTriangle4(buf2, buf4[0], buf4[1], buf4[2]);	//copy 3d triangle to 2d

		//centered image
		buf2[0][0] += WINDOW_WIDTH / 2;
		buf2[0][1] += WINDOW_HEIGHT / 2;
		buf2[1][0] += WINDOW_WIDTH / 2;
		buf2[1][1] += WINDOW_HEIGHT / 2;
		buf2[2][0] += WINDOW_WIDTH / 2;
		buf2[2][1] += WINDOW_HEIGHT / 2;

		drawTriangle(renderer, buf2);					//draw 2d triangle
	}
	//deleting defined matrices
	delMat4(P);
	delMat4(X);
	delMat4(Y);
	delMat4(Z);
	delMat4(M);
	delTriangle(buf2);
	delTriangle(buf4);
}

void drawTriangle(SDL_Renderer * renderer, Triangle2i triangle){
	SDL_RenderDrawLine(renderer, triangle[0][0], triangle[0][1], triangle[1][0], triangle[1][1]);
	SDL_RenderDrawLine(renderer, triangle[1][0], triangle[1][1], triangle[2][0], triangle[2][1]);
	SDL_RenderDrawLine(renderer, triangle[2][0], triangle[2][1], triangle[0][0], triangle[0][1]);
}
