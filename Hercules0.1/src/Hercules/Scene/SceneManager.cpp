#include "hcpch.h"

#include "SceneManager.h"

namespace Hercules {

	SceneData sceneData;

	void SceneManager::PrintStats()
	{
		HC_CORE_STAT("Test Components: {0}", sceneData.TestComponents.size());
		HC_CORE_STAT("Mesh Components: {0}", sceneData.MeshComponents.size());
		HC_CORE_STAT("Transform Components: {0}", sceneData.TransformComponents.size());
		HC_CORE_STAT("Light Components: {0}", sceneData.LightComponents.size());
	}

	void SceneManager::NewComponent(Component& c, unsigned int id)
	{
		//NOTE:
		/*
		Here is where i need to continue working, and switching from a universal light class to
		multiple
		
		
		
		*/

		switch (c.GetType())
		{
		case ComponentType::Mesh:
			sceneData.MeshComponents.insert(std::pair<unsigned int, MeshComponent>(id, (MeshComponent&)c));
			break;
		case ComponentType::Test:
			sceneData.TestComponents.insert(std::pair<unsigned int, DemoComponent>(id, (DemoComponent&)c));
			break;
		case ComponentType::Transform:
			sceneData.TransformComponents.insert(std::pair<unsigned int, TransformComponent>(id, (TransformComponent&)c));
			break;
		case ComponentType::DirectionalLight:
			sceneData.LightComponents.insert(std::pair<unsigned int, DirectionalLight>(id, (DirectionalLight&)c));
			break;
		case ComponentType::SpotLight:
			sceneData.LightComponents.insert(std::pair<unsigned int, SpotLight>(id, (SpotLight&)c));
			break;
		case ComponentType::PointLight:
			sceneData.LightComponents.insert(std::pair<unsigned int, PointLight>(id, (PointLight&)c));
			break;
		case ComponentType::Material:
			sceneData.MaterialComponents.insert(std::pair<unsigned int, MaterialComponent>(id, (MaterialComponent&)c));
			break;
		}
	}

	void SceneManager::NewEntity(std::string name)
	{
		sceneData.Entities.insert(std::pair<unsigned int, std::string> (sceneData.Entities.size() + 1, name));
	}

	void SceneManager::DeleteComponent(ComponentType c, unsigned int id)
	{
		switch (c)
		{
		case ComponentType::Light:
			sceneData.LightComponents.erase(id);
			break;
		case ComponentType::Test:
			sceneData.TestComponents.erase(id);
			break;
		case ComponentType::Mesh:
			sceneData.MeshComponents.erase(id);
			break;
		case ComponentType::Material:
			sceneData.MaterialComponents.erase(id);
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

	MaterialComponent* SceneManager::GetMaterialComponent(unsigned int id)
	{
		for (std::map<unsigned int, MaterialComponent>::iterator it = sceneData.MaterialComponents.begin(); it != sceneData.MaterialComponents.end(); ++it)
		{
			if ((*it).first == id)
			{
				return &(*it).second;
			}
		}
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

	bool SceneManager::HasTestComponent(unsigned int id)
	{
		for (std::map<unsigned int, DemoComponent>::iterator it = sceneData.TestComponents.begin(); it != sceneData.TestComponents.end(); ++it)
		{
			if ((*it).first == id)
			{
				return true;
			}
		}
		return false;
	}

	bool SceneManager::HasMaterialComponent(unsigned int id)
	{
		for (std::map<unsigned int, MaterialComponent>::iterator it = sceneData.MaterialComponents.begin(); it != sceneData.MaterialComponents.end(); ++it)
		{
			if ((*it).first == id)
			{
				return true;
			}
		}
		return false;
	}

	DemoComponent* SceneManager::GetDemoComponent(unsigned int id)
	{
		for (std::map<unsigned int, DemoComponent>::iterator it = sceneData.TestComponents.begin(); it != sceneData.TestComponents.end(); ++it)
		{
			if ((*it).first == id)
			{
				return &(*it).second;
			}
		}
	}

	std::map<unsigned int, DemoComponent>& SceneManager::GetDemoComponentList()
	{
		return sceneData.TestComponents;
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

	std::map<unsigned int, MaterialComponent>& SceneManager::GetMaterialComponentList()
	{
		return sceneData.MaterialComponents;
	}

	std::map<unsigned int, std::string>& SceneManager::GetEntites()
	{
		return sceneData.Entities;
	}

	void SceneManager::NewTexture(const char* name, const char* path)
	{
		//ID automatically changes when generating a texture
		sceneData.textures.insert(std::pair<const char*, Texture>(name, Texture(path, 1, HC_IMG_JPG)));
	}

	Texture* SceneManager::GetTexture(const char* name)
	{
		for (std::map<const char*, Texture>::iterator it = sceneData.textures.begin(); it != sceneData.textures.end(); ++it)
		{
			if ((*it).first == name)
			{
				return &(*it).second;
			}
		}
	}

	std::map<const char*, Texture>& SceneManager::GetTextureList()
	{
		return sceneData.textures;
	}

	void SceneManager::IncrementPointLights()
	{
		sceneData.PointLights++;
	}

	void SceneManager::DecrementPointLights()
	{
		sceneData.PointLights--;
	}

	const int SceneManager::GetPointLightsCount()
	{
		return sceneData.PointLights;
	}

}