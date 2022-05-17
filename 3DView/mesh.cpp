#include "mesh.h"

void Mesh::DrawGuro(int nX, int nY, double dScale) const
{
	for (const auto& objFace : m_vecFaces)
	{
		double dLengthNormal = std::sqrt(m_vecNormales[objFace.iEl1].dX * m_vecNormales[objFace.iEl1].dX +
			m_vecNormales[objFace.iEl1].dY * m_vecNormales[objFace.iEl1].dY + 
			m_vecNormales[objFace.iEl1].dZ * m_vecNormales[objFace.iEl1].dZ);
		double ax = m_vecNormales[objFace.iEl1].dX / dLengthNormal;
		double ay = m_vecNormales[objFace.iEl1].dY / dLengthNormal;
		double az = m_vecNormales[objFace.iEl1].dZ / dLengthNormal;
		double dIntensity1 = abs(m_TLight.dX * ax + m_TLight.dY * ay + m_TLight.dZ * az) * 255;
		dLengthNormal = std::sqrt(m_vecNormales[objFace.iEl2].dX * m_vecNormales[objFace.iEl2].dX +
			m_vecNormales[objFace.iEl2].dY * m_vecNormales[objFace.iEl2].dY +
			m_vecNormales[objFace.iEl2].dZ * m_vecNormales[objFace.iEl2].dZ);
		ax = m_vecNormales[objFace.iEl2].dX / dLengthNormal;
		ay = m_vecNormales[objFace.iEl2].dY / dLengthNormal;
		az = m_vecNormales[objFace.iEl2].dZ / dLengthNormal;
		double dIntensity2 = abs(m_TLight.dX * ax + m_TLight.dY * ay + m_TLight.dZ * az) * 255;
		dLengthNormal = std::sqrt(m_vecNormales[objFace.iEl3].dX * m_vecNormales[objFace.iEl3].dX +
			m_vecNormales[objFace.iEl3].dY * m_vecNormales[objFace.iEl3].dY +
			m_vecNormales[objFace.iEl3].dZ * m_vecNormales[objFace.iEl3].dZ);
		ax = m_vecNormales[objFace.iEl3].dX / dLengthNormal;
		ay = m_vecNormales[objFace.iEl3].dY / dLengthNormal;
		az = m_vecNormales[objFace.iEl3].dZ / dLengthNormal;
		double dIntensity3 = abs(m_TLight.dX * ax + m_TLight.dY * ay + m_TLight.dZ * az) * 255;
		double x1 = m_dDist * dScale * m_vecVertices[objFace.iEl1].dX / (m_dDist - m_vecVertices[objFace.iEl1].dZ * dScale) + nX;
		double x2 = m_dDist * dScale * m_vecVertices[objFace.iEl2].dX / (m_dDist - m_vecVertices[objFace.iEl1].dZ * dScale) + nX;
		double x3 = m_dDist * dScale * m_vecVertices[objFace.iEl3].dX / (m_dDist - m_vecVertices[objFace.iEl1].dZ * dScale) + nX;
		double y1 = m_dDist * dScale * m_vecVertices[objFace.iEl1].dY / (m_dDist - m_vecVertices[objFace.iEl1].dZ * dScale) + nY;
		double y2 = m_dDist * dScale * m_vecVertices[objFace.iEl2].dY / (m_dDist - m_vecVertices[objFace.iEl2].dZ * dScale) + nY;
		double y3 = m_dDist * dScale * m_vecVertices[objFace.iEl3].dY / (m_dDist - m_vecVertices[objFace.iEl3].dZ * dScale) + nY;
		TriangleGradient(x1, y1, m_vecVertices[objFace.iEl1].dZ * dScale, x2, y2, m_vecVertices[objFace.iEl2].dZ * dScale, x3, y3, 
			m_vecVertices[objFace.iEl3].dZ * dScale, dIntensity1, dIntensity2, dIntensity3);
	}
}

void Mesh::Draw(int nX, int nY, double dScale) const
{
	for (const auto& objFace : m_vecFaces)
	{
		double ax = m_vecVertices[objFace.iEl1].dX - m_vecVertices[objFace.iEl2].dX;
		double ay = m_vecVertices[objFace.iEl1].dY - m_vecVertices[objFace.iEl2].dY;
		double az = m_vecVertices[objFace.iEl1].dZ - m_vecVertices[objFace.iEl2].dZ;

		double bx = m_vecVertices[objFace.iEl2].dX - m_vecVertices[objFace.iEl3].dX;
		double by = m_vecVertices[objFace.iEl2].dY - m_vecVertices[objFace.iEl3].dY;
		double bz = m_vecVertices[objFace.iEl2].dZ - m_vecVertices[objFace.iEl3].dZ;
		double dNormalX = ay * bz - az * by;
		double dNormalY = az * bx - ax * bz;
		double dNormalZ = ax * by - ay * bx;
		double dLengthNormal = sqrt(dNormalX * dNormalX + dNormalY * dNormalY + dNormalZ * dNormalZ);
		dNormalX = dNormalX / dLengthNormal;
		dNormalY = dNormalY / dLengthNormal;
		dNormalZ = dNormalZ / dLengthNormal;
		double dIntensity = abs(m_TLight.dX * dNormalX + m_TLight.dY * dNormalY + m_TLight.dZ * dNormalZ) * 255;
		double x1 = m_dDist * dScale * m_vecVertices[objFace.iEl1].dX / (m_dDist - m_vecVertices[objFace.iEl1].dZ * dScale) + nX;
		double x2 = m_dDist * dScale * m_vecVertices[objFace.iEl2].dX / (m_dDist - m_vecVertices[objFace.iEl1].dZ * dScale) + nX;
		double x3 = m_dDist * dScale * m_vecVertices[objFace.iEl3].dX / (m_dDist - m_vecVertices[objFace.iEl1].dZ + dScale) + nX;
		double y1 = m_dDist * dScale * m_vecVertices[objFace.iEl1].dY / (m_dDist - m_vecVertices[objFace.iEl1].dZ * dScale) + nY;
		double y2 = m_dDist * dScale * m_vecVertices[objFace.iEl2].dY / (m_dDist - m_vecVertices[objFace.iEl2].dZ * dScale) + nY;
		double y3 = m_dDist * dScale * m_vecVertices[objFace.iEl3].dY / (m_dDist - m_vecVertices[objFace.iEl3].dZ * dScale) + nY;
		Triangle(x1, y1, m_vecVertices[objFace.iEl1].dZ * dScale, x2, y2, m_vecVertices[objFace.iEl2].dZ * dScale, x3, y3, 
			 m_vecVertices[objFace.iEl3].dZ * dScale, dIntensity);
	}
}

void Mesh::Rotate(double dAngleX)
{
	const double dCosConst = std::cos(dAngleX * DEG);
	const double dSinConst = std::sin(dAngleX * DEG);
	// Rotate Vertices
	for (auto& objVertex : m_vecVertices)
	{
		
		double dTemp = objVertex.dX * dCosConst - objVertex.dZ * dSinConst;
		objVertex.dZ = objVertex.dX * dSinConst + objVertex.dZ * dCosConst;
		objVertex.dX = dTemp;
		dTemp = objVertex.dX * dCosConst - objVertex.dZ * dSinConst;
		objVertex.dZ = objVertex.dX * dSinConst + objVertex.dZ * dCosConst;
		objVertex.dX = dTemp;
		dTemp = objVertex.dX * dCosConst - objVertex.dZ * dSinConst;
		objVertex.dZ = objVertex.dX * dSinConst + objVertex.dZ * dCosConst;
		objVertex.dX = dTemp;
	}

	// Rotate Normales
	for (auto& objVertex : m_vecNormales)
	{
		double dTemp = objVertex.dX * dCosConst - objVertex.dZ * dSinConst;
		objVertex.dZ = objVertex.dX * dSinConst + objVertex.dZ * dCosConst;
		objVertex.dX = dTemp;
		dTemp = objVertex.dX * dCosConst - objVertex.dZ * dSinConst;
		objVertex.dZ = objVertex.dX * dSinConst + objVertex.dZ * dCosConst;
		objVertex.dX = dTemp;
		dTemp = objVertex.dX * dCosConst - objVertex.dZ * dSinConst;
		objVertex.dZ = objVertex.dX * dSinConst + objVertex.dZ * dCosConst;
		objVertex.dX = dTemp;
	}
}

void Mesh::CreateFromFile(const std::string& sFileName)
{
	std::ifstream in(sFileName);
	if (in)
	{
		// get length of file
		in.seekg(0, in.end);
		size_t lengthOfFile = in.tellg();
		in.seekg(0, in.beg);
		auto DrawProgressBar = [&in, &lengthOfFile]()
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

		auto Split = [](const std::string_view& s, char sep = ' ') -> std::vector<std::string>
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
		};
		

		std::thread threadOfProgressBar(DrawProgressBar);

		std::string line;
		while (std::getline(in, line))
		{
			std::vector<std::string> vecStr = Split(line);
			if (!vecStr.empty())
			{
				if (vecStr[0] == "v")
				{
					m_vecVertices.emplace_back(Vertex{ std::stod(vecStr[1]), -std::stod(vecStr[2]), std::stod(vecStr[3]) });
				}
				if (vecStr[0] == "vn")
				{
					m_vecNormales.emplace_back(Vertex{ std::stod(vecStr[1]), std::stod(vecStr[2]), std::stod(vecStr[3]) });
				}
				if (vecStr[0] == "f")
				{
					std::vector<std::string> vecStr1 = Split(vecStr[1], '/');
					std::vector<std::string> vecStr2 = Split(vecStr[2], '/');
					std::vector<std::string> vecStr3 = Split(vecStr[3], '/');
					m_vecFaces.emplace_back(Face{std::stoi(vecStr1[0]) - 1, std::stoi(vecStr2[0]) - 1, std::stoi(vecStr3[0]) - 1});

					if (vecStr.size() > 4)
					{
						std::vector<std::string> vecStr4 = Split(vecStr[4], '/');
						m_vecFaces.emplace_back(Face{ std::stoi(vecStr1[0]) - 1, std::stoi(vecStr3[0]) - 1, std::stoi(vecStr4[0]) - 1 });
					}
				}
			}
		}
		threadOfProgressBar.join();
		in.close();
	}
}


void Mesh::CorrectXYZ()
{
	double dXMin = 0.0;
	double dXMax = 0.0;
	double dYMin = 0.0;
	double dYMax = 0.0;
	double dZMin = 0.0;
	double dZMax = 0.0;
	
	for (const auto& objVertex : m_vecVertices)
	{
		if(objVertex.dX < dXMin) dXMin = objVertex.dX;
		if(dXMax < objVertex.dX) dXMax = objVertex.dX;
		if(objVertex.dY < dYMin) dYMin = objVertex.dY;
		if(dYMax < objVertex.dY) dYMax = objVertex.dY;
		if(objVertex.dZ < dZMin) dZMin = objVertex.dZ;
		if(dZMax < objVertex.dZ) dZMax = objVertex.dZ;
	}

	double dShiftX = abs(dXMax + dXMin) / 2;
	double dShiftY = abs(dYMax + dYMin) / 2;
	double dShiftZ = abs(dZMax + dZMin) / 2;

	if(abs(dXMax) > abs(dXMin)) dShiftX = -dShiftX;
	if(abs(dYMax) > abs(dYMin)) dShiftY = -dShiftY;
	if(abs(dZMax) > abs(dZMin)) dShiftZ = -dShiftZ;

	for (auto& objVertex : m_vecVertices)
	{
		objVertex.dX += dShiftX;
		objVertex.dY += dShiftY;
		objVertex.dZ += dShiftZ;
	}
}
