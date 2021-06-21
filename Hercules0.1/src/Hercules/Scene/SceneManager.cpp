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

	void SceneManager::NewComponent(unsigned int key, Component& c)
	{
		switch (c.GetType())
		{
		case ComponentType::Mesh:
			sceneData.MeshComponents.insert(std::pair<unsigned int, MeshComponent>(key, (MeshComponent&)c));
			break;
		case ComponentType::Test:
			sceneData.TestComponents.insert(std::pair<unsigned int, DemoComponent>(key, (DemoComponent&)c));
			break;
		case ComponentType::Transform:
			sceneData.TransformComponents.insert(std::pair<unsigned int, TransformComponent>(key, (TransformComponent&)c));
			break;
		case ComponentType::Light:
			sceneData.LightComponents.insert(std::pair<unsigned int, LightComponent>(key, (LightComponent&)c));
			break;
		}
	}

	void SceneManager::NewEntity(unsigned int id, const char* name)
	{
		sceneData.Entities.insert(std::pair<unsigned int, const char*>(id, name));
	}

	MeshComponent* SceneManager::GetMeshComponent(unsigned int id)
	{
		for (std::map<unsigned int, MeshComponent>::iterator it = sceneData.MeshComponents.begin(); it != sceneData.MeshComponents.end(); ++it)
		{
			if ((*it).second.GetId() == id)
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
			if ((*it).second.GetId() == id)
			{
				return &(*it).second;
			}
		}
	}

	LightComponent* SceneManager::GetLightComponent(unsigned int id)
	{
		for (std::map<unsigned int, LightComponent>::iterator it = sceneData.LightComponents.begin(); it != sceneData.LightComponents.end(); ++it)
		{
			if ((*it).second.GetId() == id)
			{
				return &(*it).second;
			}
		}
	}

	bool SceneManager::HasLightComponent(unsigned int id)
	{
		for (std::map<unsigned int, LightComponent>::iterator it = sceneData.LightComponents.begin(); it != sceneData.LightComponents.end(); ++it)
		{
			if ((*it).second.GetId() == id)
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
			if ((*it).second.GetId() == id)
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
			if ((*it).second.GetId() == id)
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

	std::map<unsigned int, const char*>& SceneManager::GetEntites()
	{
		return sceneData.Entities;
	}
	
}
