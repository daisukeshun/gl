#include "drawing.h"			//contain all drawing functions and macro
#include "types.h"				//contain custom types 
#include "objLoader.h"			//contain object loader function (old non-rewrite header file)
#include "settings.h"			//contain some global vars
#include <SDL2/SDL.h>			//drawing library


//macro for clearing renderer
//we chose black drawing color and clear renderer
#define clearRenderer(renderer)\
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);\
	SDL_RenderClear(renderer);


int main(int argc, char** argv){
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Window * window;		//our window
	SDL_Renderer * renderer1;	//our canvas

	SDL_Event event;			//sdl event (need for exit form drawing loop)
	
	//define sdl window
	window = SDL_CreateWindow("FCEngine",	//name of window
		   	SDL_WINDOWPOS_CENTERED,			//window position X
		   	SDL_WINDOWPOS_CENTERED,			//window position Y
			WINDOW_WIDTH,					//window width
		   	WINDOW_HEIGHT,					//window height
			0);								//black box
	
	//define sdl renderer
	renderer1 = SDL_CreateRenderer(
			window,						//window pointer
		   	-1,							//render id of driver
		   	SDL_RENDERER_PRESENTVSYNC);	//render flag (SDL_RENDERER_SOFTWARE, ACCELERATED, PRESENTVSYNC, TARGETTEXTURE) 
	//we use VSYNC for disable tiring of window
	
	Uint32 frameStart;			//need for calculating time of frames
	Uint32 frameTime;			//***********************************

	bool quit = False;			//indicator for quit

	defMesh(rabbit);							//mesh definition 
	loadMesh(rabbit, "Rabbit_Lowpoly_1.obj");	//(wath more in mesh.h and objLoader.h

	//camera definition
	defCamera(camera);							//define Camera *
	isCamera(camera);							//create empty camera 
	defVec3f(buf);								//empty buffer for setting camera position and rotation
	setCamera(camera, 
			buf, buf,						//zero vectors
		   	0.0001f,						//near	surface for drawing/clipping
		   	1.f,							//far	surface for drawing/clipping
		   	120,							//angle of view (in degrees)
		   	WINDOW_WIDTH/WINDOW_HEIGHT);	//aspect ratio (4:3, 5:4, 16:9, 16:10, 21:9 etc.)


	delVec(buf);							//remove empty buffer
	setVec3(camera->rotation, 0, 0, -91);	//change camera rotation

	printf("Position\n");
	logVec3(rabbit->position);				//print mesh position in terminal

	setVec3(rabbit->position, 0, 0, 50);	//change mesh world position 
	setVec3(rabbit->rotation, 180, 0, 0);	//change meshes self rotation

	while (!quit){						
		frameStart = SDL_GetTicks();		//catch start time of drawing our frame
		clearRenderer(renderer1);			//clear our canvas
		
		SDL_SetRenderDrawColor(renderer1, 255, 255, 222, 255);	//set color of drawing
		drawMesh(renderer1, camera, rabbit);					//draw each polygon in mesh
		
		frameTime = SDL_GetTicks() - frameStart;				//calculate time of frame

		//_______________________________ frame limiter ____________________________
		if (33 > frameTime){									
							SDL_Delay(33);
							SDL_RenderPresent(renderer1);
		}
		else{
							SDL_Delay(frameTime);
		}
		//__________________________________________________________________________

		//event puller (for quit press ESC btn or cross in terminal)
		while (SDL_PollEvent(&event)){
			if	(event.type == SDL_QUIT ||				//cross pressing
				 event.key.keysym.sym == SDLK_ESCAPE)	//ESC pressing
										{quit = True;}	//
			else						{quit = False;} //
		}
	}

	//deleting camera
	delCamera(camera);
	//deleting all and destroy window
	SDL_DestroyRenderer(renderer1);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
