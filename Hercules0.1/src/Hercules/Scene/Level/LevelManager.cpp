#include "hcpch.h"

#include "LevelManager.h"

namespace Hercules {
	
	LevelData levelData;
	
	const void Hercules::LevelManager::OpenLevel(const char* levelPath)
	{
		std::ifstream levelFile(levelPath);
		std::string line;
		//std::stringstream levelData;
		//levelData << levelFile.rdbuf();
		int lineNR = 1;
		while (std::getline(levelFile, line))
		{
			std::string delimiter = "[";
			if (line.find(delimiter) != std::string::npos)
			{
				//HC_CORE_TRACE("Header: {0}: {1}", lineNR, line);
				line.erase(0, line.find(delimiter) + delimiter.length());
				std::string name = line.substr(0, line.find("]"));
				levelData.names.push_back(name);
			}
			//else
			//{
				//HC_CORE_TRACE("Line {0}: {1}", lineNR, line);
				//lineNR++;
			//}

		}

		levelFile.close();

		//std::string string = levelData.str();
		//HC_CORE_TRACE(string);
	}

	const std::vector<std::string> LevelManager::GetNames()
	{
		return levelData.names;
	}

}