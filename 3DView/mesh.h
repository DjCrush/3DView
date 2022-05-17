#pragma once
#include <vector>
#include <string>
#include "graphicslib.h"
#include <SDL.h>
#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

class Mesh {
public:
	struct Vertex
	{
		double dX;
		double dY;
		double dZ; 
	};
	struct Face
	{
		int iEl1;
		int iEl2;
		int iEl3;
	};
	Mesh() = default;
	void Draw(int nX, int nY, double dScale) const;
	void DrawGouraud(int nX, int nY, double dScale) const;
	void Rotate(double dAngleX);
	void CreateFromFile(const std::string& sFileName);
	void CorrectXYZ();
	bool NormalesAreExist() const;
private:
	Vertex m_TLight{ 0.0, 0.0, 1.0 };
	double m_dDist{ 35500.0 };
	
	std::vector <Face> m_vecFaces;
	std::vector <Vertex> m_vecVertices;
	std::vector <Vertex> m_vecNormales;
};
