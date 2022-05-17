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
	if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;

	window = SDL_CreateWindow(
		"ObjViewer",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		SCREEN_WIDTH,                               // width, in pixels
		SCREEN_HEIGHT,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	Mesh mesh;
	mesh.CreateFromFile(argv[1]);
	while (!keypress)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				keypress = 1;
				break;
			case SDL_KEYDOWN:
				keypress = 1;
				break;
			}
		}
		SDL_RenderClear(renderer);
		ClearScreen();
		mesh.Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.50);
		mesh.Rotate(1);
		SDL_RenderPresent(renderer);
	}
	delete[] Z_buffer;
	SDL_FreeSurface(font);
	SDL_FreeSurface(screen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
