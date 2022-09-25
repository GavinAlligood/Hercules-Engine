#include "hcpch.h"

#include "SceneManager.h"

namespace Hercules {

	SceneData sceneData;

	void SceneManager::PrintStats()
	{
		HC_CORE_STAT("Mesh Components: {0}", sceneData.MeshComponents.size());
		HC_CORE_STAT("Transform Components: {0}", sceneData.TransformComponents.size());
		HC_CORE_STAT("Light Components: {0}", sceneData.LightComponents.size());
	}

	void SceneManager::NewComponent(Component& c, unsigned int id)
	{
		switch (c.GetType())
		{
		case ComponentType::Mesh:
			sceneData.MeshComponents.insert(std::pair<unsigned int, MeshComponent>(id, (MeshComponent&)c));
			break;
		case ComponentType::Transform:
			sceneData.TransformComponents.insert(std::pair<unsigned int, TransformComponent>(id, (TransformComponent&)c));
			break;
		case ComponentType::DirectionalLight:
			sceneData.DirectionalLightComponents.insert(std::pair<unsigned int, DirectionalLight>(id, (DirectionalLight&)c));
			break;
		case ComponentType::SpotLight:
			sceneData.SpotLightComponents.insert(std::pair<unsigned int, SpotLight>(id, (SpotLight&)c));
			break;
		case ComponentType::PointLight:
			sceneData.PointLightComponents.insert(std::pair<unsigned int, PointLight>(id, (PointLight&)c));
			break;
		}
	}

	void SceneManager::NewEntity(std::string name)
	{
		sceneData.Entities.insert(std::pair<unsigned int, std::string>(sceneData.Entities.size() + 1, name));
	}

	void SceneManager::DeleteComponent(ComponentType c, unsigned int id)
	{
		switch (c)
		{
		case ComponentType::Transform:
			sceneData.TransformComponents.erase(id);
			break;
		case ComponentType::DirectionalLight:
			sceneData.DirectionalLightComponents.erase(id);
			break;
		case ComponentType::PointLight:
			sceneData.PointLightComponents.erase(id);
			break;
		case ComponentType::SpotLight:
			sceneData.SpotLightComponents.erase(id);
			break;
		case ComponentType::Mesh:
			sceneData.MeshComponents.erase(id);
			break;
		}
	}

	void SceneManager::DeleteEntity(unsigned int id)
	{
		sceneData.Entities.erase(id);
	}

	MeshComponent* SceneManager::GetMeshComponent(unsigned int id)
	{
		for (std::map<unsigned int, MeshComponent>::iterator it = sceneData.MeshComponents.begin(); it != sceneData.MeshComponents.end(); ++it)
		{
			if ((*it).first == id)
			{
				return &(*it).second;
			}
		}
	}

	TransformComponent* SceneManager::GetTransformComponent(unsigned int id)
	{
		for (std::map<unsigned int, TransformComponent>::iterator it = sceneData.TransformComponents.begin(); it != sceneData.TransformComponents.end(); ++it)
		{
			if ((*it).first == id)
			{
				return &(*it).second;
			}
		}
	}

	LightComponent* SceneManager::GetLightComponent(unsigned int id)
	{
		for (std::map<unsigned int, LightComponent>::iterator it = sceneData.LightComponents.begin(); it != sceneData.LightComponents.end(); ++it)
		{
			if ((*it).first == id)
			{
				return &(*it).second;
			}
		}
	}

	DirectionalLight* SceneManager::GetDirectionalLightComponent(unsigned int id)
	{
		for (std::map<unsigned int, DirectionalLight>::iterator it = sceneData.DirectionalLightComponents.begin(); it != sceneData.DirectionalLightComponents.end(); ++it)
		{
			if ((*it).first == id)
			{
				return &(*it).second;
			}
		}
	}

	PointLight* SceneManager::GetPointLightComponent(unsigned int id)
	{
		for (std::map<unsigned int, PointLight>::iterator it = sceneData.PointLightComponents.begin(); it != sceneData.PointLightComponents.end(); ++it)
		{
			if ((*it).first == id)
			{
				return &(*it).second;
			}
		}
	}

	SpotLight* SceneManager::GetSpotLightComponent(unsigned int id)
	{
		for (std::map<unsigned int, SpotLight>::iterator it = sceneData.SpotLightComponents.begin(); it != sceneData.SpotLightComponents.end(); ++it)
		{
			if ((*it).first == id)
			{
				return &(*it).second;
			}
		}
	}

	bool SceneManager::HasMeshComponent(unsigned int id)
	{
		for (std::map<unsigned int, MeshComponent>::iterator it = sceneData.MeshComponents.begin(); it != sceneData.MeshComponents.end(); ++it)
		{
			if ((*it).first == id)
			{
				return true;
			}
		}
		return false;
	}

	bool SceneManager::HasLightComponent(unsigned int id)
	{
		for (std::map<unsigned int, LightComponent>::iterator it = sceneData.LightComponents.begin(); it != sceneData.LightComponents.end(); ++it)
		{
			if ((*it).first == id)
			{
				return true;
			}
		}
		return false;
	}

	bool SceneManager::HasDirectionalLight(unsigned int id)
	{
		for (std::map<unsigned int, DirectionalLight>::iterator it = sceneData.DirectionalLightComponents.begin(); it != sceneData.DirectionalLightComponents.end(); ++it)
		{
			if ((*it).first == id)
			{
				return true;
			}
		}
		return false;
	}

	bool SceneManager::HasPointLight(unsigned int id)
	{
		for (std::map<unsigned int, PointLight>::iterator it = sceneData.PointLightComponents.begin(); it != sceneData.PointLightComponents.end(); ++it)
		{
			if ((*it).first == id)
			{
				return true;
			}
		}
		return false;
	}

	bool SceneManager::HasSpotLight(unsigned int id)
	{
		for (std::map<unsigned int, SpotLight>::iterator it = sceneData.SpotLightComponents.begin(); it != sceneData.SpotLightComponents.end(); ++it)
		{
			if ((*it).first == id)
			{
				return true;
			}
		}
		return false;
	}

	bool SceneManager::HasTransformComponent(unsigned int id)
	{
		for (std::map<unsigned int, TransformComponent>::iterator it = sceneData.TransformComponents.begin(); it != sceneData.TransformComponents.end(); ++it)
		{
			if ((*it).first == id)
			{
				return true;
			}
		}
		return false;
	}

	std::map<unsigned int, MeshComponent>& SceneManager::GetMeshComponentList()
	{
		return sceneData.MeshComponents;
	}

	std::map<unsigned int, TransformComponent>& SceneManager::GetTransformComponentList()
	{
		return sceneData.TransformComponents;
	}

	std::map<unsigned int, LightComponent>& SceneManager::GetLightComponentList()
	{
		return sceneData.LightComponents;
	}

	std::map<unsigned int, DirectionalLight>& SceneManager::GetDirectionalLightList()
	{
		return sceneData.DirectionalLightComponents;
	}

	std::map<unsigned int, PointLight>& SceneManager::GetPointLightList()
	{
		return sceneData.PointLightComponents;
	}

	std::map<unsigned int, SpotLight>& SceneManager::GetSpotLightList()
	{
		return sceneData.SpotLightComponents;
	}

	std::map<unsigned int, std::string>& SceneManager::GetEntities()
	{
		return sceneData.Entities;
	}

	void SceneManager::NewTexture(std::string name, const char* path, bool type)
	{
		//ID automatically changes when generating a texture
		if (!type)
		{
			sceneData.Textures.insert(std::pair<std::string, Texture>(name, Texture(path, 1, false)));
		}
		else 
		{
			sceneData.Textures.insert(std::pair<std::string, Texture>(name, Texture(path, 1, true)));
		}
	}

	Texture* SceneManager::GetTexture(const char* name)
	{
		for (std::map<std::string, Texture>::iterator it = sceneData.Textures.begin(); it != sceneData.Textures.end(); ++it)
		{
			if ((*it).first == name)
			{
				return &(*it).second;
			}
		}
	}

	//Finds the material name associated with a certain texture
	std::string SceneManager::GetTextureName(Texture& texture)
	{
		//1. Loop through texture list
		//2. Check if given texture matches texture in the list
		//3. return name associated with that texture

		for (std::map<std::string, Texture>::iterator it = sceneData.Textures.begin(); it != sceneData.Textures.end(); ++it)
		{
			if ((*it).second.GetID() == texture.GetID())
			{
				return (*it).first;
			}
		}
	}

	glm::vec3 SceneManager::GetColor(const char* name)
	{
		for (std::map<std::string, glm::vec3>::iterator it = sceneData.Colors.begin(); it != sceneData.Colors.end(); ++it)
		{
			if ((*it).first == name)
			{
				return (*it).second;
			}
		}
	}

	float SceneManager::GetShiny(const char* name)
	{
		for (std::map<std::string, float>::iterator it = sceneData.Shiny.begin(); it != sceneData.Shiny.end(); ++it)
		{
			if ((*it).first == name)
			{
				return (*it).second;
			}
		}
	}

	std::map<std::string, Texture>& SceneManager::GetTextureList()
	{
		return sceneData.Textures;
	}

	std::map<std::string, glm::vec3>& SceneManager::GetColorList()
	{
		return sceneData.Colors;
	}

	std::map<std::string, float>& SceneManager::GetShinyList()
	{
		return sceneData.Shiny;
	}

	void SceneManager::AppendMaterial(std::string name)
	{
		
	}

	const glm::vec3 SceneManager::GetBackgroundColor()
	{
		return sceneData.BackgroundColor;
	}

	void SceneManager::SetBackgroundColor(glm::vec3 color)
	{
		sceneData.BackgroundColor = color;
	}

	void SceneManager::SetBackgroundColor(float r, float g, float b)
	{
		sceneData.BackgroundColor = glm::vec3(r, g, b);
	}
}