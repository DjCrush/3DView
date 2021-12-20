#pragma once
#include <vector>
#include <SDL.h>
#include <limits>

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 800;
const double DEG = 0.017453292519943295;
extern SDL_Renderer* renderer;
extern SDL_Surface* screen;
extern SDL_Surface* font;

extern int* Z_buffer;

void ClearScreen();
void Triangle(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int col);
void TriangleGradient(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int col1, int col2, int col3);
