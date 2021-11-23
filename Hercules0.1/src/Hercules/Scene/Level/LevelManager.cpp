#include "hcpch.h"

#include "LevelManager.h"

namespace Hercules {
	
	LevelData levelData;
	
	const void Hercules::LevelManager::OpenLevel(const char* levelPath)
	{
		HC_STAT("Opening {0}", levelPath);

		levelData.matColors.clear();
		levelData.matShinies.clear();

		SceneManager::GetEntites().clear();
		SceneManager::GetTransformComponentList().clear();
		SceneManager::GetLightComponentList().clear();
		SceneManager::GetDemoComponentList().clear();
		SceneManager::GetMeshComponentList().clear();
		SceneManager::GetDirectionalLightList().clear();
		SceneManager::GetPointLightList().clear();
		SceneManager::GetSpotLightList().clear();
		SceneManager::GetMaterialComponentList().clear();
		SceneManager::GetTextureList().clear();

		std::string line;
		std::ifstream levelFile(levelPath);
		int lineNR = 1;
		
		unsigned int id = 1;

		std::string delimiter = "#";
		std::string colon = ":";
		std::string pos = "P";
		std::string rot = "R";
		std::string scale = "S";
		std::string color = "C";
		std::string tex = "T";
		std::string shiny = "H";
		std::string mesh = "V";
		std::string mat = "M";

		//Read materials
		HC_CORE_STAT("Loading materials...");
		for (auto& i : std::filesystem::directory_iterator("Assets/Materials"))
		{
			std::string path = i.path().string();
			std::ifstream material(path);

			std::string name = "";

			bool currentType = 0;

			while (std::getline(material, line))
			{
				if (line.find(delimiter) != std::string::npos)
				{
					line.erase(0, line.find(delimiter) + delimiter.length());
					currentType = std::stoi(line);
				}
				else if (line.find(tex) != std::string::npos)
				{
					line.erase(0, line.find(tex) + tex.length());
					name = i.path().filename().string().substr(0,
						i.path().filename().string().find("."));
					SceneManager::NewTexture(name,
						line.c_str(), currentType);
				}
				else if (line.find(color) != std::string::npos)
				{
					if (line.substr(0, 1) == color)
					{
						line.erase(0, line.find(color) + color.length());
						std::string r = line.substr(0, line.find("r"));
						line.erase(0, line.find("r") + color.length());
						std::string g = line.substr(0, color.find("g"));
						line.erase(0, line.find("g") + color.length());
						std::string b = line.substr(0, line.find("b"));
						levelData.matColors.insert(std::pair<std::string, glm::vec3>
							(name, glm::vec3(std::stof(r), std::stof(g), std::stof(b))));
					}
				}
				else if (line.find(shiny) != std::string::npos)
				{
					if (line.substr(0, 1) == shiny)
					{
						line.erase(0, line.find(shiny) + shiny.length());
						levelData.matShinies.insert(std::pair<std::string,
							float>(name, std::stof(line)));
					}
				}
			}
		}
		HC_CORE_SUCCESS("Materials loaded");

		//Read level file
		HC_CORE_STAT("Loading {0}...", levelPath);
		while (std::getline(levelFile, line))
		{
			if (line.find(delimiter) != std::string::npos)
			{
				line.erase(0, line.find(delimiter) + delimiter.length());
				std::string name = line.substr(0, line.find(colon));
				line.erase(0, line.find(colon) + colon.length());
				id = std::stoi(line.substr(0, line.find(colon)));
				SceneManager::NewEntity(name);
			}
			else if (line.find(pos) != std::string::npos)
			{
				if (line.substr(0, 1) == pos)
				{
					//Position
					line.erase(0, line.find(pos) + pos.length());
					std::string px = line.substr(0, line.find("x"));
					line.erase(0, line.find("x") + pos.length());
					std::string py = line.substr(0, line.find("y"));
					line.erase(0, line.find("y") + pos.length());
					std::string pz = line.substr(0, line.find("z"));

					//Scale
					line.erase(0, line.find(scale) + scale.length());
					std::string sx = line.substr(0, line.find("x"));
					line.erase(0, line.find("x") + scale.length());
					std::string sy = line.substr(0, line.find("y"));
					line.erase(0, line.find("y") + scale.length());
					std::string sz = line.substr(0, line.find("z"));

					//Rotation
					line.erase(0, line.find(rot) + rot.length());
					std::string rx = line.substr(0, line.find("x"));
					line.erase(0, line.find("x") + rot.length());
					std::string ry = line.substr(0, line.find("y"));
					line.erase(0, line.find("y") + rot.length());
					std::string rz = line.substr(0, line.find("z"));

					SceneManager::NewComponent(TransformComponent(glm::vec3(std::stof(px), std::stof(py), std::stof(pz)),
						glm::vec3(std::stof(sx), std::stof(sy), std::stof(sz)), 
						glm::vec3(std::stof(rx), std::stof(ry), std::stof(rz))), SceneManager::GetEntites().size());
				}
			}
			else if (line.find("DL") != std::string::npos)
			{
				SceneManager::NewComponent(DirectionalLight(), id);
			}
			else if (line.find("T") != std::string::npos)
			{
				SceneManager::NewComponent(DemoComponent(), id);
			}
			if (line.find(mesh) != std::string::npos)
			{
				if (line.substr(0, 1) == mesh)
				{
					line.erase(0, line.find(mesh) + mesh.length());
					SceneManager::NewComponent(MeshComponent(line), id);
				}
			}
			if (line.find(mat) != std::string::npos)
			{
				if (line.substr(0, 1) == mat)
				{
					line.erase(0, line.find(mat) + mat.length());
					std::string m = line.substr(0, line.find(mat));
					SceneManager::NewComponent(MaterialComponent(
						SceneManager::GetTexture(m.c_str()), *GetColor(m)), id);
					SceneManager::GetMaterialComponent(id)->SetName(m);
				}
			}
			if (line.find(color) != std::string::npos)
			{
				if (line.substr(0, 1) == color)
				{
					line.erase(0, line.find(color) + color.length());
					std::string r = line.substr(0, line.find("r"));
					line.erase(0, line.find("r") + color.length());
					std::string g = line.substr(0, color.find("g"));
					line.erase(0, line.find("g") + color.length());
					std::string b = line.substr(0, line.find("b"));

					SceneManager::GetMaterialComponent(id)->SetColor(glm::vec3(
						std::stof(r), std::stof(g), std::stof(b)));
				}
			}
			if (line.find(shiny) != std::string::npos)
			{
				if (line.substr(0, 1) == shiny)
				{
					line.erase(0, line.find(shiny) + shiny.length());
					SceneManager::GetMaterialComponent(id)->SetShininess(std::stof(line));
				}
			}
		}

		levelFile.close();
		HC_CORE_SUCCESS("{0} loaded", levelPath);

		//ProcessMaterials(levelPath);
	}

	void LevelManager::ProcessMaterials(const char* levelPath)
	{
		std::ifstream levelFile(levelPath);
		std::string line;
		std::string mat = "M";
		std::string delimiter = "#";
		std::string colon = ":";
		std::string color = "C";
		std::string shiny = "H";
		unsigned int id = 0;

		while (std::getline(levelFile, line))
		{
			if (line.find(delimiter) != std::string::npos)
			{
				line.erase(0, line.find(delimiter) + delimiter.length());
				line.erase(0, line.find(colon) + colon.length());
				id = std::stoi(line.substr(0, line.find(colon)));
			}
			else if (line.find(mat) != std::string::npos)
			{
				if (line.substr(0, 1) == mat)
				{
					line.erase(0, line.find(mat) + mat.length());
					std::string m = line.substr(0, line.find(mat));
					SceneManager::NewComponent(MaterialComponent(
						SceneManager::GetTexture(m.c_str()), *GetColor(m)), id);
					SceneManager::GetMaterialComponent(id)->SetName(m);
				}
			}
			else if (line.find(color) != std::string::npos)
			{
				line.erase(0, line.find(color) + color.length());
				std::string r = line.substr(0, line.find("r"));
				line.erase(0, line.find("r") + color.length());
				std::string g = line.substr(0, color.find("g"));
				line.erase(0, line.find("g") + color.length());
				std::string b = line.substr(0, line.find("b"));

				SceneManager::GetMaterialComponent(id)->SetColor(glm::vec3(
					std::stof(r), std::stof(g), std::stof(b)));
			}
			else if (line.find(shiny) != std::string::npos)
			{
				if (line.substr(0, 1) == shiny)
				{
					line.erase(0, line.find(shiny) + shiny.length());
					SceneManager::GetMaterialComponent(id)->SetShininess(std::stof(line));
				}
			}
		}
	}

	//Saving level
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
				TransformComponent t = *SceneManager::GetTransformComponent(i.first);
				
				//Every entity will have a transform
				file_out << "\n#" << i.second <<
					":" << i.first << std::endl;
				file_out << "P" << t.GetPos().x << "x"
					<< t.GetPos().y << "y" << t.GetPos().z
					<< "z" << "S" << t.GetScale().x << "x"
					<< t.GetScale().y << "y" << t.GetScale().z
					<< "z" << "R" << t.GetRotation().x << "x"
					<< t.GetRotation().y << "y" << t.GetRotation().z
					<< "z" << std::endl;

				if (SceneManager::HasDirectionalLight(i.first))
					file_out << "DL" << std::endl;

				if (SceneManager::HasTestComponent(i.first))
					file_out << "T" << std::endl;

				if (SceneManager::HasMeshComponent(i.first))
				{
					file_out << "V" <<
						SceneManager::GetMeshComponent(i.first)->GetPath() << std::endl;
					HC_TRACE("Saved mesh: {0}", SceneManager::GetMeshComponent(i.first)->GetPath());
				}
				if (SceneManager::HasMaterialComponent(i.first))
				{
					file_out << "M" <<
						SceneManager::GetMaterialComponent(i.first)->GetName() << std::endl;
					file_out << "H" <<
						SceneManager::GetMaterialComponent(i.first)->GetShininess() << std::endl;
					file_out << "C" <<
						SceneManager::GetMaterialComponent(i.first)->GetColor().x << "r" <<
						SceneManager::GetMaterialComponent(i.first)->GetColor().y << "g" <<
						SceneManager::GetMaterialComponent(i.first)->GetColor().z << "b" << std::endl;
				}
			}
			
			HC_CORE_SUCCESS("{0} Saved succesfully!", levelPath);
		}

		file_out.close();
	}

	const void LevelManager::NewLevel(std::string levelName)
	{
		std::string path = "Levels/" + levelName + ".hclvl";
		std::ofstream file_out(path);
		HC_CORE_SUCCESS("New Level: {0}", path);
	}

	glm::vec3* LevelManager::GetColor(std::string name)
	{
		for (auto& i : levelData.matColors)
		{
			if (i.first == name)
			{
				return &i.second;
			}
		}
	}

	float* LevelManager::GetShininess(std::string name)
	{
		for (auto& i : levelData.matShinies)
		{
			if (i.first == name)
			{
				return &i.second;
			}
		}
	}
}