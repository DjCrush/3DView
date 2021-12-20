#include <SDL.h>
#include <Windows.h>
#include "graphicslib.h"
#include "mesh.h"

#undef main

SDL_Surface* screen;
SDL_Surface* font;
SDL_Renderer* renderer;
int* Z_buffer = new int[SCREEN_WIDTH * SCREEN_HEIGHT];

int main()
{
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
	if (!(font = SDL_LoadBMP("font.bmp")))
	{
		MessageBoxA(NULL, "File 'font.bmp' not found", "Error", MB_OK);
		SDL_Quit();
		return 1;
	}
	Mesh tor;
	//tor.ReadOBJFile("E:/EXP/3dmax/obj/1.obj");
	tor.ReadFromFile("E:/EXP/3dmax/obj/bmw.obj");
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
		//tor.Draw(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 120.0);
		tor.DrawGuro(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 300.0);
		tor.Rotate(1);
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
