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
		case ComponentType::Light:
			sceneData.LightComponents.insert(std::pair<unsigned int, LightComponent>(id, (LightComponent&)c));
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
		return false;
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

	std::map<unsigned int, MaterialComponent>& SceneManager::GetMaterialComponentList()
	{
		return sceneData.MaterialComponents;
	}

	std::map<unsigned int, std::string>& SceneManager::GetEntites()
	{
		return sceneData.Entities;
	}
	
}
