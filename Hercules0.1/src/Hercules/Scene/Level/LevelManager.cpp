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
			else if (line.find("DL") != std::string::npos)
			{
				SceneManager::NewComponent(DirectionalLight(), id);
			}
			else if (line.find("T") != std::string::npos)
			{
				SceneManager::NewComponent(DemoComponent(), id);
			}
		}
		levelFile.close();
	}

	const void LevelManager::WriteLevel(const char* levelPath)
	{
		std::fstream file_out;

		file_out.open(levelPath, std::ios::out);
		if (!file_out.is_open())
		{
			HC_CORE_ERROR("Failed to open level");
		}
		else
		{
			for (auto &i : SceneManager::GetEntites())
			{
				TransformComponent* t = SceneManager::GetTransformComponent(i.first);

				file_out << "\n#" << i.second <<
					":" << i.first << std::endl;
				file_out << "P" << t->GetPos().x << "x"
					<< t->GetPos().y << "y" << t->GetPos().z
					<< "z" << std::endl;
				file_out << "S" << t->GetScale().x << "x"
					<< t->GetScale().y << "y" << t->GetScale().z
					<< "z" << std::endl;
				file_out << "R" << t->GetRotation().x << "x"
					<< t->GetRotation().y << "y" << t->GetRotation().z
					<< "z" << std::endl;

				if (SceneManager::HasDirectionalLight(i.first))
					file_out << "DL" << std::endl;

				if (SceneManager::HasTestComponent(i.first))
					file_out << "T" << std::endl;
			}
			
			HC_CORE_TRACE("Saved succesfully!");
		}

		file_out.close();
	}

	void LevelManager::OpenMaterial()
	{
		//SceneManager::NewTexture("Plastic", "Assets/Textures/default_texture.jpg");
		//SceneManager::NewTexture("Dirt", "Assets/Textures/dirtMinecraft.jpg");
		levelData.Materials.push_back("Plastic");
		levelData.Materials.push_back("Dirt");

		for (auto& i : std::filesystem::directory_iterator("Assets/Materials"))
		{
			std::string red = "R";
			std::string green = "G";
			std::string blue = "B";
			std::string tex = "T";

			//std::string path = "Assets/Materials/" + i.path().filename() + ".hcmat";
			std::string path = i.path().string();
			HC_CORE_TRACE(i.path().string());
			std::ifstream material(path);
			std::string line;

			while (std::getline(material, line))
			{
				if (line.find(red) != std::string::npos)
				{
					line.erase(0, line.find(red) + red.length());
					std::string rs = line.substr(0, line.find(red));
				}
				else if (line.find(green) != std::string::npos)
				{
					line.erase(0, line.find(green) + green.length());
					std::string gs = line.substr(0, line.find(green));
				}
				else if (line.find(blue) != std::string::npos)
				{
					line.erase(0, line.find(blue) + blue.length());
					std::string bs = line.substr(0, line.find(blue));
				}
				else if (line.find(tex) != std::string::npos)
				{
					line.erase(0, line.find(tex) + tex.length());
					/*HC_CORE_TRACE(i.path().filename().string().substr(0, 
						i.path().filename().string().find(".")));*/
					std::string name = i.path().filename().string().substr(0,
						i.path().filename().string().find("."));
					SceneManager::NewTexture(name,
						line.c_str());
				}
			}
		}

		for (auto &i : levelData.Materials)
		{
			
		}	
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
		for (auto &i : levelData.positions)
		{
			if (i.first == id)
			{
				return &i.second;
			}
		}
	}

	glm::vec3* LevelManager::GetScale(unsigned int id)
	{
		for (auto &i : levelData.scales)
		{
			if (i.first == id)
			{
				return &i.second;
			}
		}
	}

	glm::vec3* LevelManager::GetRotation(unsigned int id)
	{
		for (auto &i : levelData.rotations)
		{
			if (i.first == id)
			{
				return &i.second;
			}
		}
	}

}