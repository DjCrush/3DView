#pragma once
#include <vector>
#include <string>
#include <cmath>
#include "graphicslib.h"
#include <SDL.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <SDL_timer.h>
#include <tuple>
#include <thread>
#include <chrono>

class Mesh {
public:
	struct Vertex
	{
		double dX;
		double dY;
		double dZ; 
		double dXN;
		double dYN;
		double dZN;
	};
	struct Face
	{
		Vertex vertex1;
		Vertex vertex2;
		Vertex vertex3;
	};
	Mesh() = default;
	void Draw(int nX, int nY, double dScale) const;
	void DrawGuro(int nX, int nY, double dScale) const;
	void Rotate(double dAngleX);
	void CreateFromFile(const std::string& sFileName);
private:
	double m_dLightX{ 0.0 };
	double m_dLightY{ 0.0 };
	double m_dLightZ{ 1.0 };
	double m_dDist{ 35500.0 };
	
	std::vector<std::string> Split(const std::string_view& s, char sep = ' ') const;
	std::vector <Face> m_vecFace;
};
