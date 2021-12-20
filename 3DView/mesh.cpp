#include "mesh.h"

void Mesh::DrawGuro(int nX, int nY, double dScale)
{
	for (const auto& objFace : m_vecFace)
	{
		double dLengthNormal = sqrt(objFace.vertex1.dXN * objFace.vertex1.dXN + objFace.vertex1.dYN * objFace.vertex1.dYN + objFace.vertex1.dZN * objFace.vertex1.dZN);
		double ax = objFace.vertex1.dXN / dLengthNormal;
		double ay = objFace.vertex1.dYN / dLengthNormal;
		double az = objFace.vertex1.dZN / dLengthNormal;
		double dIntensity1 = abs(m_dLightX * ax + m_dLightY * ay + m_dLightZ * az) * 255;
		dLengthNormal = sqrt(objFace.vertex2.dXN * objFace.vertex2.dXN + objFace.vertex2.dYN * objFace.vertex2.dYN + objFace.vertex2.dZN * objFace.vertex2.dZN);
		ax = objFace.vertex2.dXN / dLengthNormal;
		ay = objFace.vertex2.dYN / dLengthNormal;
		az = objFace.vertex2.dZN / dLengthNormal;
		double dIntensity2 = abs(m_dLightX * ax + m_dLightY * ay + m_dLightZ * az) * 255;
		dLengthNormal = sqrt(objFace.vertex3.dXN * objFace.vertex3.dXN + objFace.vertex3.dYN * objFace.vertex3.dYN + objFace.vertex3.dZN * objFace.vertex3.dZN);
		ax = objFace.vertex3.dXN / dLengthNormal;
		ay = objFace.vertex3.dYN / dLengthNormal;
		az = objFace.vertex3.dZN / dLengthNormal;
		double dIntensity3 = abs(m_dLightX * ax + m_dLightY * ay + m_dLightZ * az) * 255;
		double x1 = m_dDist * dScale * objFace.vertex1.dX / (m_dDist - objFace.vertex1.dZ * dScale) + nX;
		double x2 = m_dDist * dScale * objFace.vertex2.dX / (m_dDist - objFace.vertex2.dZ * dScale) + nX;
		double x3 = m_dDist * dScale * objFace.vertex3.dX / (m_dDist - objFace.vertex3.dZ * dScale) + nX;
		double y1 = m_dDist * dScale * objFace.vertex1.dY / (m_dDist - objFace.vertex1.dZ * dScale) + nY;
		double y2 = m_dDist * dScale * objFace.vertex2.dY / (m_dDist - objFace.vertex2.dZ * dScale) + nY;
		double y3 = m_dDist * dScale * objFace.vertex3.dY / (m_dDist - objFace.vertex3.dZ * dScale) + nY;
		TriangleGradient(x1, y1, objFace.vertex1.dZ * dScale, x2, y2, objFace.vertex2.dZ * dScale, x3, y3, objFace.vertex3.dZ * dScale, dIntensity1, dIntensity2, dIntensity3);
	}
}

void Mesh::Draw(int nX, int nY, double dScale)
{
	for (const auto& objFace : m_vecFace)
	{
		double ax = objFace.vertex1.dX - objFace.vertex2.dX;
		double ay = objFace.vertex1.dY - objFace.vertex2.dY;
		double az = objFace.vertex1.dZ - objFace.vertex2.dZ;
		double bx = objFace.vertex2.dX - objFace.vertex3.dX;
		double by = objFace.vertex2.dY - objFace.vertex3.dY;
		double bz = objFace.vertex2.dZ - objFace.vertex3.dZ;
		double dNormalX = ay * bz - az * by;
		double dNormalY = az * bx - ax * bz;
		double dNormalZ = ax * by - ay * bx;
		double dLengthNormal = sqrt(dNormalX * dNormalX + dNormalY * dNormalY + dNormalZ * dNormalZ);
		dNormalX = dNormalX / dLengthNormal;
		dNormalY = dNormalY / dLengthNormal;
		dNormalZ = dNormalZ / dLengthNormal;
		double dIntensity = abs(m_dLightX * dNormalX + m_dLightY * dNormalY + m_dLightZ * dNormalZ);
		double x1 = m_dDist * dScale * objFace.vertex1.dX / (m_dDist - objFace.vertex1.dZ * dScale) + nX;
		double x2 = m_dDist * dScale * objFace.vertex2.dX / (m_dDist - objFace.vertex2.dZ * dScale) + nX;
		double x3 = m_dDist * dScale * objFace.vertex3.dX / (m_dDist - objFace.vertex3.dZ * dScale) + nX;
		double y1 = m_dDist * dScale * objFace.vertex1.dY / (m_dDist - objFace.vertex1.dZ * dScale) + nY;
		double y2 = m_dDist * dScale * objFace.vertex2.dY / (m_dDist - objFace.vertex2.dZ * dScale) + nY;
		double y3 = m_dDist * dScale * objFace.vertex3.dY / (m_dDist - objFace.vertex3.dZ * dScale) + nY;
		Triangle(x1, y1, objFace.vertex1.dZ * dScale, x2, y2, objFace.vertex2.dZ * dScale, x3, y3, objFace.vertex3.dZ * dScale, dIntensity * 255);
	}
}

void Mesh::Rotate(double dAngleX)
{
	const double dCosConst = cos(dAngleX * DEG);
	const double dSinConst = sin(dAngleX * DEG);
	for (auto& objFace : m_vecFace)
	{
		// Rotate vertexes
		double dTemp = objFace.vertex1.dX * dCosConst - objFace.vertex1.dZ * dSinConst;
		objFace.vertex1.dZ = objFace.vertex1.dX * dSinConst + objFace.vertex1.dZ * dCosConst;
		objFace.vertex1.dX = dTemp;
		dTemp = objFace.vertex2.dX * dCosConst - objFace.vertex2.dZ * dSinConst;
		objFace.vertex2.dZ = objFace.vertex2.dX * dSinConst + objFace.vertex2.dZ * dCosConst;
		objFace.vertex2.dX = dTemp;
		dTemp = objFace.vertex3.dX * dCosConst - objFace.vertex3.dZ * dSinConst;
		objFace.vertex3.dZ = objFace.vertex3.dX * dSinConst + objFace.vertex3.dZ * dCosConst;
		objFace.vertex3.dX = dTemp;

		// Rotate normals
		dTemp = objFace.vertex1.dXN * dCosConst - objFace.vertex1.dZN * dSinConst;
		objFace.vertex1.dZN = objFace.vertex1.dXN * dSinConst + objFace.vertex1.dZN * dCosConst;
		objFace.vertex1.dXN = dTemp;
		dTemp = objFace.vertex2.dXN * dCosConst - objFace.vertex2.dZN * dSinConst;
		objFace.vertex2.dZN = objFace.vertex2.dXN * dSinConst + objFace.vertex2.dZN * dCosConst;
		objFace.vertex2.dXN = dTemp;
		dTemp = objFace.vertex3.dXN * dCosConst - objFace.vertex3.dZN * dSinConst;
		objFace.vertex3.dZN = objFace.vertex3.dXN * dSinConst + objFace.vertex3.dZN * dCosConst;
		objFace.vertex3.dXN = dTemp;
	}
}

void Mesh::ReadFromFile(const std::string& sFileName)
{
	std::vector<std::tuple<double, double, double>> vecVertex;
	std::vector<std::tuple<double, double, double>> vecNormal;
	std::ifstream in(sFileName);
	if (in)
	{
		// get length of file
		in.seekg(0, in.end);
		auto nLengthFile{ in.tellg() };
		in.seekg(0, in.beg);
		auto nOldTime{ SDL_GetTicks() + 200 };
		std::string line;
		while (std::getline(in, line))
		{
			std::string sTempLine;
			std::stringstream sStreamTemp(line);
			sStreamTemp >> sTempLine;
			if (sTempLine == "v")
			{
				double dX, dY, dZ;
				sStreamTemp >> dX >> dY >> dZ;
				vecVertex.push_back(std::make_tuple(dX, -dY, dZ));
			}
			if (sTempLine == "vn")
			{
				double dX, dY, dZ;
				sStreamTemp >> dX >> dY >> dZ;
				vecNormal.push_back(std::make_tuple(dX, dY, dZ));
			}
			if (sTempLine == "f")
			{
				std::string item_t;
				std::vector<std::tuple<int, int, int>> vector_t;
				int nCounterVertex{ 0 };
				while (sStreamTemp >> item_t)
				{
					std::stringstream item{ item_t };
					std::string sIndexVertex{ "0" }, sIndexTexture{ "0" }, sIndexNormal{ "0" };
					std::getline(item, sIndexVertex, '/');
					std::getline(item, sIndexTexture, '/');
					std::getline(item, sIndexNormal);
					std::tuple<int, int, int> tp = std::make_tuple(std::stoi(sIndexVertex), std::stoi(sIndexTexture), std::stoi(sIndexNormal));
					vector_t.push_back(tp);

					if (nCounterVertex == 2)
					{
						size_t point1 = std::get<0>(vector_t[0]) - 1;
						size_t point2 = std::get<0>(vector_t[1]) - 1;
						size_t point3 = std::get<0>(vector_t[2]) - 1;
						size_t point_normal1 = std::get<2>(vector_t[0]) - 1;
						size_t point_normal2 = std::get<2>(vector_t[1]) - 1;
						size_t point_normal3 = std::get<2>(vector_t[2]) - 1;
						m_vecFace.push_back(Face{ Vertex{std::get<0>(vecVertex[point1]), std::get<1>(vecVertex[point1]), std::get<2>(vecVertex[point1]), std::get<0>(vecNormal[point_normal1]), std::get<1>(vecNormal[point_normal1]), std::get<2>(vecNormal[point_normal1])},
										Vertex{std::get<0>(vecVertex[point2]), std::get<1>(vecVertex[point2]), std::get<2>(vecVertex[point2]), std::get<0>(vecNormal[point_normal2]), std::get<1>(vecNormal[point_normal2]), std::get<2>(vecNormal[point_normal2]) },
										Vertex{std::get<0>(vecVertex[point3]), std::get<1>(vecVertex[point3]), std::get<2>(vecVertex[point3]), std::get<0>(vecNormal[point_normal3]), std::get<1>(vecNormal[point_normal3]), std::get<2>(vecNormal[point_normal3])} });

					}
					else if (nCounterVertex > 2)
					{
					//	size_t point1 = std::get<0>(vector_t[nCounterVertex - 1]) - 1;
					//	size_t point2 = std::get<0>(vector_t[nCounterVertex]) - 1;
					//	size_t point3 = std::get<0>(vector_t[nCounterVertex - 2]) - 1;
					//	size_t point_normal1 = std::get<2>(vector_t[nCounterVertex - 1]) - 1;
					//	size_t point_normal2 = std::get<2>(vector_t[nCounterVertex]) - 1;
					//	size_t point_normal3 = std::get<2>(vector_t[nCounterVertex - 2]) - 1;
					//	m_vecFace.push_back(Face{ Vertex{std::get<0>(vecVertex[point1]), std::get<1>(vecVertex[point1]), std::get<2>(vecVertex[point1]), std::get<0>(vecNormal[point_normal1]), std::get<1>(vecNormal[point_normal1]), std::get<2>(vecNormal[point_normal1])},
					//					Vertex{std::get<0>(vecVertex[point2]), std::get<1>(vecVertex[point2]), std::get<2>(vecVertex[point2]), std::get<0>(vecNormal[point_normal2]), std::get<1>(vecNormal[point_normal2]), std::get<2>(vecNormal[point_normal2]) },
					//					Vertex{std::get<0>(vecVertex[point3]), std::get<1>(vecVertex[point3]), std::get<2>(vecVertex[point3]), std::get<0>(vecNormal[point_normal3]), std::get<1>(vecNormal[point_normal3]), std::get<2>(vecNormal[point_normal3])} });
					}
					nCounterVertex++;
				}
			}
			if (SDL_GetTicks() > nOldTime)
			{
				nOldTime = SDL_GetTicks() + 200;
				SDL_Rect Rect { 0, 0, SCREEN_WIDTH * in.tellg() / nLengthFile, 38 };
				SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(renderer, &Rect);
				SDL_RenderPresent(renderer);
			}
		}
		SDL_Rect Rect { 0, 0, SCREEN_WIDTH, 38 };
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &Rect);
		SDL_RenderPresent(renderer);
	}
}
