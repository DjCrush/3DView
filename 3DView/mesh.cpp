#include "mesh.h"

void Mesh::DrawGuro(int nX, int nY, double dScale) const
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

void Mesh::Draw(int nX, int nY, double dScale) const
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

void Mesh::CreateFromFile(const std::string& sFileName)
{
	struct Point { double x, y, z; };
	std::vector<Point> vecVertex;
	std::vector<Point> vecNormal;
	std::ifstream in(sFileName);
	if (in)
	{
		// get length of file
		in.seekg(0, in.end);
		size_t lengthOfFile = in.tellg();
		in.seekg(0, in.beg);
		auto DrawProgressWidget = [&in, &lengthOfFile]()
		{
			while (true)
			{
				size_t currentSize = in.tellg();
				SDL_Rect Rect{0, 0, static_cast<int>(SCREEN_WIDTH * static_cast<double>(currentSize) / lengthOfFile), 38};
				SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderFillRect(renderer, &Rect);
				SDL_RenderPresent(renderer);
				std::this_thread::sleep_for(std::chrono::milliseconds(40));
				if (currentSize >= lengthOfFile)
				{
					break;
				}
			}
			SDL_Rect Rect{ 0, 0, SCREEN_WIDTH, 38 };
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect(renderer, &Rect);
			SDL_RenderPresent(renderer);
		};
		

		std::thread threadOfProgressBar(DrawProgressWidget);

		std::string line;
		while (std::getline(in, line))
		{
			std::vector<std::string> vecStr = Split(line);
			if (!vecStr.empty())
			{
				if (vecStr[0] == "v")
				{
					vecVertex.emplace_back(Point{ std::stod(vecStr[1]), -std::stod(vecStr[2]), std::stod(vecStr[3]) });
				}
				if (vecStr[0] == "vn")
				{
					vecNormal.emplace_back(Point{ std::stod(vecStr[1]), std::stod(vecStr[2]), std::stod(vecStr[3]) });
				}
				if (vecStr[0] == "f")
				{
					std::vector<std::string> vecStr1 = Split(vecStr[1], '/');
					std::vector<std::string> vecStr2 = Split(vecStr[2], '/');
					std::vector<std::string> vecStr3 = Split(vecStr[3], '/');
					m_vecFace.emplace_back(Face{
						Vertex{vecVertex[std::stoi(vecStr1[0]) - 1].x, vecVertex[std::stoi(vecStr1[0]) - 1].y, vecVertex[std::stoi(vecStr1[0]) - 1].z, 0.0, 0.0, 0.0},
						Vertex{vecVertex[std::stoi(vecStr2[0]) - 1].x, vecVertex[std::stoi(vecStr2[0]) - 1].y, vecVertex[std::stoi(vecStr2[0]) - 1].z, 0.0, 0.0, 0.0},
						Vertex{vecVertex[std::stoi(vecStr3[0]) - 1].x, vecVertex[std::stoi(vecStr3[0]) - 1].y, vecVertex[std::stoi(vecStr3[0]) - 1].z, 0.0, 0.0, 0.0},
						});

					if (vecStr.size() > 4)
					{
						std::vector<std::string> vecStr4 = Split(vecStr[4], '/');
						m_vecFace.emplace_back(Face{
							Vertex{vecVertex[std::stoi(vecStr1[0]) - 1].x, vecVertex[std::stoi(vecStr1[0]) - 1].y, vecVertex[std::stoi(vecStr1[0]) - 1].z, 0.0, 0.0, 0.0},
							Vertex{vecVertex[std::stoi(vecStr3[0]) - 1].x, vecVertex[std::stoi(vecStr3[0]) - 1].y, vecVertex[std::stoi(vecStr3[0]) - 1].z, 0.0, 0.0, 0.0},
							Vertex{vecVertex[std::stoi(vecStr4[0]) - 1].x, vecVertex[std::stoi(vecStr4[0]) - 1].y, vecVertex[std::stoi(vecStr4[0]) - 1].z, 0.0, 0.0, 0.0},
							});
					}
				}
			}
		}
		threadOfProgressBar.join();
		in.close();
	}
}

std::vector<std::string> Mesh::Split(const std::string_view& s, char sep) const
{
	std::vector<std::string> vecStrings;
	auto it1 = s.begin();
	bool bIsNotSeparator = false;
	for (auto it = s.begin(); it != s.end(); ++it)
	{
		if (*it != sep && !bIsNotSeparator)
		{
			it1 = it;
			bIsNotSeparator = true;
		}
		if (*it == sep && bIsNotSeparator)
		{
			bIsNotSeparator = false;
			vecStrings.emplace_back(it1, it);
		}
	}
	if (bIsNotSeparator)
		vecStrings.emplace_back(it1, s.end());
	return vecStrings;
}
