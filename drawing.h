#pragma once
#include "graphics.h"
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
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

	defMat4f(cM);
	createTranslation(cM, camera->position);
	//projection matrix 	
	defMat4f(P);
	createProjectionMatrix(P, camera);

	//logVec4(P[0]);
	//logVec4(P[1]);
	//logVec4(P[2]);
	//logVec4(P[3]);

	//printf("\n");
	defVec3f(normal);
	defVec3f(line1);
	defVec3f(line2);
	for(int i = 0; i < (int)mesh->polNum; i++){

		setTriangle4(buf4,				//copy in buffer polygon
				mesh->polygons[i][0],	//for transform it later
				mesh->polygons[i][1], 
				mesh->polygons[i][2]); 
		
		matMul4f(buf4[0], Z, buf4[0]);	//rotate
		matMul4f(buf4[1], Z, buf4[1]);	//polygon
		matMul4f(buf4[2], Z, buf4[2]);	//in Z axis

		matMul4f(buf4[0], Y, buf4[0]);	//rotate  
		matMul4f(buf4[1], Y, buf4[1]);	//polygon
		matMul4f(buf4[2], Y, buf4[2]);	//in Y axis

		matMul4f(buf4[0], X, buf4[0]);	//rotate
		matMul4f(buf4[1], X, buf4[1]);	//polygon
		matMul4f(buf4[2], X, buf4[2]);	//in X axis

		matMul4f(buf4[0], M, buf4[0]);	//transform 
		matMul4f(buf4[1], M, buf4[1]);	//polygon
		matMul4f(buf4[2], M, buf4[2]);	//in world coords
		
		matMul4f(buf4[0], cM, buf4[0]);	//transform  
		matMul4f(buf4[1], cM, buf4[1]);	//polygon
		matMul4f(buf4[2], cM, buf4[2]);	//in camera position

		setVec3(line1,
			   	buf4[1][0] - buf4[0][0], 
			   	buf4[1][1] - buf4[0][1], 
			   	buf4[1][2] - buf4[0][2]);

		setVec3(line2,
			   	buf4[1][0] - buf4[2][0], 
			   	buf4[1][1] - buf4[2][1], 
			   	buf4[1][2] - buf4[2][2]);

		//get normal vector
		cross3f(normal, line2, line1);

		//length of normal
		float l = sqrtf(
			normal[0]*normal[0] +
			normal[1]*normal[1] +
			normal[2]*normal[2]);

		//normal is single vector
		normal[0] /= l;
		normal[1] /= l;
		normal[2] /= l;

		if(normal[2] < 0){


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
	}
	//deleting defined matrices
	delVec(normal);
	delVec(line1);
	delVec(line2);
	delMat4(P);
	delMat4(X);
	delMat4(Y);
	delMat4(Z);
	delMat4(M);
	delTriangle(buf2);
	delTriangle(buf4);
}

void drawTriangle(SDL_Renderer * renderer, Triangle2i triangle){

	defVec2i(buf);
	//sort our triangles in polygon
	if(triangle[1][1] > triangle[0][1]) {
		setVec2(buf,
				triangle[0][0],
				triangle[0][1]);

		setVec2(triangle[0],
			   	triangle[1][0],
			   	triangle[1][1]);

		setVec2(triangle[1],
			   	buf[0],
			   	buf[1]);
	}
	if(triangle[2][1] > triangle[1][1]) {
		setVec2(buf,
				triangle[1][0],
				triangle[1][1]);

		setVec2(triangle[1],
			   	triangle[2][0],
			   	triangle[2][1]);

		setVec2(triangle[2],
			   	buf[0],
			   	buf[1]);
	}
	if(triangle[0][1] > triangle[2][1]) {
		setVec2(buf,
				triangle[2][0],
				triangle[2][1]);

		setVec2(triangle[2],
			   	triangle[0][0],
			   	triangle[0][1]);

		setVec2(triangle[0],
			   	buf[0],
			   	buf[1]);
	}
	//triangle[1] - middle point of triangle
	
	int total_height = triangle[2][1] - triangle[0][1];
	int x = 0;
	printf("x - %d\n", x);
	int y = triangle[1][1];
	printf("y - %d\n", y);

	delVec(buf);

	SDL_RenderDrawLine(renderer, 0, 0, x, y);

	SDL_RenderDrawLine(renderer, triangle[0][0], triangle[0][1], triangle[1][0], triangle[1][1]);
	SDL_RenderDrawLine(renderer, triangle[1][0], triangle[1][1], triangle[2][0], triangle[2][1]);
	SDL_RenderDrawLine(renderer, triangle[2][0], triangle[2][1], triangle[0][0], triangle[0][1]);

}
