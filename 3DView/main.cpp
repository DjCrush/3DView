#include <SDL.h>
#include "graphicslib.h"
#include "mesh.h"

#undef main

SDL_Surface* screen;
SDL_Surface* font;
SDL_Renderer* renderer;
int* Z_buffer = new int[SCREEN_WIDTH * SCREEN_HEIGHT];

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		std::cerr << "USAGE: 3DView <filename>" << std::endl;
		return -1;
	}
	SDL_Event event;
	SDL_Window* window = nullptr;
	int keypress = 0;
	double scale = 1.0;
	bool bIsDrawGuro = true;
	bool bIsRun = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

	window = SDL_CreateWindow(
		"3DView",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		SCREEN_WIDTH,                               // width, in pixels
		SCREEN_HEIGHT,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	Mesh mesh;
	mesh.CreateFromFile(argv[1]);
	mesh.CorrectXYZ();
	while (bIsRun)
	{
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_MOUSEWHEEL:
					if (event.wheel.y > 0) 
					{
						scale += 0.1;
					}
					else if (event.wheel.y < 0)
					{
						scale -= 0.1;
					}
				break;
				case SDL_QUIT:
					bIsRun = false;
					break;
				case SDL_KEYDOWN:
					bIsDrawGuro = !bIsDrawGuro;
					break;
			}
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 180, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		ResetZBuffer();
		if(bIsDrawGuro && mesh.NormalesAreExist())
			mesh.DrawGouraud(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, std::exp(scale));
		else
			mesh.Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, std::exp(scale));
		SDL_RenderPresent(renderer);
		mesh.Rotate(1);
	}
	delete[] Z_buffer;
	SDL_FreeSurface(font);
	SDL_FreeSurface(screen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
