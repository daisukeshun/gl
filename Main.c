#include "includes.h"
#pragma warning(disable:4996)

#define clearRenderer(renderer) \
SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); \
SDL_RenderClear(renderer);


int main(void) {

	Mesh* Rabbit = loadObject("Meshes/Rabbit_Lowpoly_03.obj");

	// Triangle3d generate array of float[3][3] (NEED REWORK)
	fMatrix rotationX = createTriangle3d();
	createRotationX(rotationX, 0);
	fMatrix rotationY = createTriangle3d();
	createRotationX(rotationY, 0);
	fMatrix rotationZ = createTriangle3d();
	createRotationX(rotationZ, 0);


	//basicaly model turned upside down
	createRotationX(rotationX, 180);
	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;
		Uint32 frameStart;

		int frameTime;
		if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) == 0)
		{
			SDL_bool done = SDL_FALSE;
			float angle = 0;
			Triangle3d buf3d = createTriangle3d();
			Triangle2d buf2d = createTriangle2d();

			while (!done)
			{
				SDL_Event event;
				frameStart = SDL_GetTicks(); // catch start time of drawing our frame

				clearRenderer(renderer);

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

				//TODO: Drawing something there
				angle += 5;
				if (angle == 360)
				{
					angle = 0;
				}

				createRotationY(rotationY, angle);

				// rotate polygons and project them on screen 
				for (int i = 0; i < Rabbit->pNum; i++)
				{
					rotateTriangle(buf3d, rotationX, Rabbit->polygons[i]);
					rotateTriangle(buf3d, rotationY, buf3d);
					toTriangle2d(buf2d, buf3d);
					drawTriangle2d(renderer, buf2d);
				}
				SDL_RenderPresent(renderer); // This function draw all, what we write upper


				// if our frame time more than 33ms (for 30fps)
				//delay per frames will be equal frame time 
				//else delay will be 33ms

				frameTime = SDL_GetTicks() - frameStart;

				if ((1000 / 30) > frameTime)
				{
					SDL_Delay(1000 / 30);
				}
				else
				{
					SDL_Delay(frameTime);
				}
				while (SDL_PollEvent(&event))
				{

					if (event.type == SDL_QUIT)
					{
						done = SDL_TRUE;
					}
				}

			}
		}


		deletefArray(rotationX, 3);
		deletefArray(rotationY, 3);
		deletefArray(rotationZ, 3);

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}

		SDL_Quit();
	}

	deleteMesh(Rabbit);

	return 0;
}