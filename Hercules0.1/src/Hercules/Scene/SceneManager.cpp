#include "hcpch.h"

#include "SceneManager.h"

namespace Hercules {

	SceneData sceneData;

	void SceneManager::PrintStats()
	{
		HC_CORE_STAT("Test Components: {0}", sceneData.TestComponents.size());
		HC_CORE_STAT("Mesh Components: {0}", sceneData.MeshComponents.size());
		HC_CORE_STAT("Transform Components: {0}", sceneData.TransformComponents.size());
	}

	void SceneManager::AppendComponent(unsigned int key, Component& c)
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
		}
	}

#pragma region Later
	/*bool SceneManager::GetMeshComponent(unsigned int id)
	{
		for (std::map<unsigned int, MeshComponent>::iterator it = sceneData.MeshComponents.begin(); it != sceneData.MeshComponents.end(); ++it)
		{
			if ((*it).second.GetId() == id)
			{
				return true;
			}
		}
		return false;
	}

	bool SceneManager::GetTransformComponent(unsigned int id)
	{
		for (std::map<unsigned int, TransformComponent>::iterator it = sceneData.TransformComponents.begin(); it != sceneData.TransformComponents.end(); ++it)
		{
			if ((*it).second.GetId() == id)
			{
				return true;
			}
			return false;
		}
	}

	bool SceneManager::GetDemoComponent(unsigned int id)
	{
		for (std::map<unsigned int, DemoComponent>::iterator it = sceneData.TestComponents.begin(); it != sceneData.TestComponents.end(); ++it)
		{
			if ((*it).second.GetId() == id)
			{
				return true;
			}
		}
		return false;
	}*/
#pragma endregion

	std::map<unsigned int, TransformComponent>::iterator SceneManager::GetTransformComponent(unsigned int key)
	{
		std::map<unsigned int, TransformComponent>::iterator it = sceneData.TransformComponents.find(key);
		if (it != sceneData.TransformComponents.end())
		{
			return it;
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
	
}
