#include "hcpch.h"

#include "LevelManager.h"

namespace Hercules {
	
	LevelData levelData;
	
	const void Hercules::LevelManager::OpenLevel(const char* levelPath)
	{
		std::ifstream levelFile(levelPath);
		int lineNR = 1;
		std::string line;
		unsigned int id = 1;
		while (std::getline(levelFile, line))
		{
			std::string delimiter = "#";
			std::string colon = ":";
			std::string pos = "P";
			std::string rot = "R";
			std::string scale = "S";
			if (line.find(delimiter) != std::string::npos)
			{
				line.erase(0, line.find(delimiter) + delimiter.length());
				std::string name = line.substr(0, line.find(colon));
				line.erase(0, line.find(colon) + colon.length());
				id = std::stoi(line.substr(0, line.find(colon)));
				levelData.names.push_back(name);
			}
			else if (line.find(pos) != std::string::npos)
			{
				line.erase(0, line.find(pos) + pos.length());
				std::string x = line.substr(0, line.find("x"));
				line.erase(0, line.find("x") + pos.length());
				std::string y = line.substr(0, line.find("y"));
				line.erase(0, line.find("y") + pos.length());
				std::string z = line.substr(0, line.find("z"));

				levelData.positions.insert(std::pair<unsigned int, glm::vec3>
					(id, glm::vec3(std::stof(x), std::stof(y), std::stof(z))));
			}
			else if (line.find(rot) != std::string::npos)
			{
				line.erase(0, line.find(rot) + rot.length());
				std::string x = line.substr(0, line.find("x"));
				line.erase(0, line.find("x") + rot.length());
				std::string y = line.substr(0, line.find("y"));
				line.erase(0, line.find("y") + rot.length());
				std::string z = line.substr(0, line.find("z"));

				levelData.rotations.insert(std::pair<unsigned int, glm::vec3>
					(id, glm::vec3(std::stof(x), std::stof(y), std::stof(z))));
			}
			else if (line.find(scale) != std::string::npos)
			{
				line.erase(0, line.find(scale) + scale.length());
				std::string x = line.substr(0, line.find("x"));
				line.erase(0, line.find("x") + scale.length());
				std::string y = line.substr(0, line.find("y"));
				line.erase(0, line.find("y") + scale.length());
				std::string z = line.substr(0, line.find("z"));

				levelData.scales.insert(std::pair<unsigned int, glm::vec3>
					(id, glm::vec3(std::stof(x), std::stof(y), std::stof(z))));
			}
		}
		levelFile.close();
	}

	std::vector<std::string> LevelManager::GetNames()
	{
		return levelData.names;
	}

	std::map<unsigned int, glm::vec3>& LevelManager::GetPositions()
	{
		return levelData.positions;
	}

	std::map<unsigned int, glm::vec3>& LevelManager::GetScales()
	{
		return levelData.scales;
	}

	std::map<unsigned int, glm::vec3>& LevelManager::GetRotations()
	{
		return levelData.rotations;
	}

	glm::vec3* LevelManager::GetPosition(unsigned int id)
	{
		for (auto i : levelData.positions)
		{
			if (i.first == id)
			{
				return &i.second;
			}
		}
	}

	glm::vec3* LevelManager::GetScale(unsigned int id)
	{
		for (auto i : levelData.scales)
		{
			if (i.first == id)
			{
				return &i.second;
			}
		}
	}

	glm::vec3* LevelManager::GetRotation(unsigned int id)
	{
		for (auto i : levelData.rotations)
		{
			if (i.first == id)
			{
				return &i.second;
			}
		}
	}

}