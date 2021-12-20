#include "graphicslib.h"

void ClearScreen()
{
	for (size_t i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i)
	{
		Z_buffer[i] = std::numeric_limits<int>::min();
	}
	SDL_Rect d { 0,0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_SetRenderDrawColor(renderer, 0, 0, 75, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &d);
}

void Triangle(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int col)
{
	//if ((x1 < 0 & x2 < 0 & x3 < 0) || (x1 > SCREEN_WIDTH & x2 > SCREEN_WIDTH & x3 > SCREEN_WIDTH) || (y1 < 0 & y2 < 0 & y3 < 0) || (y1 > SCREEN_HEIGHT & y2 > SCREEN_HEIGHT & y3 > SCREEN_HEIGHT)) return;
	int x11, x12, z11, z12;
	int idx, zbb;
	double alpha, beta, th, sh;
	if (y1 > y2) { std::swap(y1, y2); std::swap(x1, x2); std::swap(z1, z2); }
	if (y1 > y3) { std::swap(y1, y3); std::swap(x1, x3); std::swap(z1, z3); }
	if (y2 > y3) { std::swap(y2, y3); std::swap(x2, x3); std::swap(z2, z3); }
	th = y3 - y1;
	sh = y2 - y1;
	if (th != 0 && sh != 0)
	{
		for (int y = y1; y < y2; ++y)
		{
			alpha = (y - y1) / th;
			beta = (y - y1) / sh;
			x11 = x1 + (x3 - x1) * alpha;
			x12 = x1 + (x2 - x1) * beta;
			z11 = z1 + (z3 - z1) * alpha;
			z12 = z1 + (z2 - z1) * beta;
			if (x12 < x11)
			{
				std::swap(x11, x12);
				std::swap(z11, z12);
			}
			if (x12 - x11 != 0)
			{
				alpha = double(z12 - z11) / (x12 - x11);
				for (int x = x11; x <= x12; ++x)
				{
					if ((x >= 0 && x < SCREEN_WIDTH) && (y >= 0 && y < SCREEN_HEIGHT))
					{
						zbb = (x - x11) * alpha + z11;
						idx = x + (y * SCREEN_WIDTH);
						if (Z_buffer[idx] < zbb)
						{
							Z_buffer[idx] = zbb;
							SDL_SetRenderDrawColor(renderer, col, col, col, SDL_ALPHA_OPAQUE);
							SDL_RenderDrawPoint(renderer, x, y);
						}
					}
				}
			}
		}
	}
	sh = y3 - y2;
	if (th != 0 && sh != 0)
	{
		for (int y = y2; y <= y3; ++y)
		{
			alpha = (y - y1) / th;
			beta = (y - y2) / sh;
			x11 = x1 + (x3 - x1) * alpha;
			x12 = x2 + (x3 - x2) * beta;
			z11 = z1 + (z3 - z1) * alpha;
			z12 = z2 + (z3 - z2) * beta;
			if (x12 < x11)
			{
				std::swap(x11, x12);
				std::swap(z11, z12);
			}
			if (x12 - x11 != 0)
			{
				alpha = double(z12 - z11) / (x12 - x11);
				for (int x = x11; x <= x12; ++x)
				{
					if ((x >= 0 && x < SCREEN_WIDTH) && (y >= 0 && y < SCREEN_HEIGHT))
					{
						zbb = (x - x11) * alpha + z11;
						idx = x + (y * SCREEN_WIDTH);
						if (Z_buffer[idx] < zbb)
						{
							Z_buffer[idx] = zbb;
							SDL_SetRenderDrawColor(renderer, col, col, col, SDL_ALPHA_OPAQUE);
							SDL_RenderDrawPoint(renderer, x, y);
						}
					}
				}
			}
		}
	}
}

void TriangleGradient(int x1, int y1, int z1, int x2, int y2, int z2, int x3, int y3, int z3, int col1, int col2, int col3)
{
	//if ((x1 < 0 & x2 < 0 & x3 < 0) || (x1 > SCREEN_WIDTH & x2 > SCREEN_WIDTH & x3 > SCREEN_WIDTH) || (y1 < 0 & y2 < 0 & y3 < 0) || (y1 > SCREEN_HEIGHT & y2 > SCREEN_HEIGHT & y3 > SCREEN_HEIGHT)) return;
	int x11, x12, z11, z12, xo1 = x1, xo2 = x2, xo3 = x3, yo1 = y1, yo2 = y2, yo3 = y3;
	int Denom = x3 * (y1 - y2) + x1 * (y2 - y3) + x2 * (y3 - y1);
	int sann = x3 * y1 - y3 * x1, tann = x1 * y2 - y1 * x2;
	double alpha, beta;
	if (!Denom) Denom = 1;
	if (y1 > y2) { std::swap(y1, y2); std::swap(x1, x2); std::swap(z1, z2); }
	if (y1 > y3) { std::swap(y1, y3); std::swap(x1, x3); std::swap(z1, z3); }
	if (y2 > y3) { std::swap(y2, y3); std::swap(x2, x3); std::swap(z2, z3); }
	double th = y3 - y1;
	double sh = y2 - y1;
	if (th != 0 && sh != 0)
	{
		for (int y = y1; y < y2; ++y)
		{
			alpha = (y - y1) / th;
			beta = (y - y1) / sh;
			x11 = x1 + (x3 - x1) * alpha;
			x12 = x1 + (x2 - x1) * beta;
			z11 = z1 + (z3 - z1) * alpha;
			z12 = z1 + (z2 - z1) * beta;
			if (x12 < x11)
			{
				std::swap(x11, x12);
				std::swap(z11, z12);
			}
			if (x12 - x11 > 10e-6)
			{
				alpha = static_cast<double>(z12 - z11) / (x12 - x11);
				for (int x = x11; x < x12; ++x)
				{
					if ((x >= 0 && x < SCREEN_WIDTH) && (y >= 0 && y < SCREEN_HEIGHT))
					{
						int zbb = (x - x11) * alpha + z11;
						int idx = x + y * SCREEN_WIDTH;
						if (Z_buffer[idx] < zbb)
						{
							Z_buffer[idx] = zbb;
							int snn = ((sann + y * (xo1 - xo3) + x * (yo3 - yo1)) << 8) / Denom;
							int tnn = ((tann + y * (xo2 - xo1) + x * (yo1 - yo2)) << 8) / Denom;
							int col = (col1 * (255 - snn - tnn) + col2 * snn + col3 * tnn) >> 8;
							SDL_SetRenderDrawColor(renderer, col, col, col, SDL_ALPHA_OPAQUE);
							SDL_RenderDrawPoint(renderer, x, y);
						}
					}
				}
			}
		}
	}
	sh = y3 - y2;
	if (th > 10e-6 && sh > 10e-6)
	{
		for (int y = y2; y <= y3; ++y)
		{
			alpha = static_cast<double>(y - y1) / th;
			beta = static_cast<double>(y - y2) / sh;
			x11 = x1 + (x3 - x1) * alpha;
			x12 = x2 + (x3 - x2) * beta;
			z11 = z1 + (z3 - z1) * alpha;
			z12 = z2 + (z3 - z2) * beta;
			if (x12 < x11)
			{
				std::swap(x11, x12);
				std::swap(z11, z12);
			}
			if (x12 - x11 > 10e-6)
			{
				alpha = static_cast<double>(z12 - z11) / (x12 - x11);
				for (int x = x11; x < x12; ++x)
				{
					if ((x >= 0 && x < SCREEN_WIDTH) && (y >= 0 && y < SCREEN_HEIGHT))
					{
						int zbb = (x - x11) * alpha + z11;
						int idx = x + y * SCREEN_WIDTH;
						if (Z_buffer[idx] < zbb)
						{
							Z_buffer[idx] = zbb;
							int snn = ((sann + y * (xo1 - xo3) + x * (yo3 - yo1)) << 8) / Denom;
							int tnn = ((tann + y * (xo2 - xo1) + x * (yo1 - yo2)) << 8) / Denom;
							int col = (col1 * (255 - snn - tnn) + col2 * snn + col3 * tnn) >> 8;
							SDL_SetRenderDrawColor(renderer, col, col, col, SDL_ALPHA_OPAQUE);
							SDL_RenderDrawPoint(renderer, x, y);
						}
					}
				}
			}
		}
	}
}