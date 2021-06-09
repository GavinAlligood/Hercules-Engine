#include "hcpch.h"

#include "SceneManager.h"

namespace Hercules {

	SceneData sceneData;

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
		}
	}

	bool SceneManager::GetMeshComponent(unsigned int id)
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

	std::map<unsigned int, DemoComponent> SceneManager::GetDemoComponents()
	{
		return sceneData.TestComponents;
	}

	std::map<unsigned int, MeshComponent> SceneManager::GetMeshComponents()
	{
		return sceneData.MeshComponents;
	}

	bool SceneManager::GetDemoComponent(unsigned int id)
	{
		HC_CORE_TRACE("Components: {0}", sceneData.TestComponents.size());

		for (std::map<unsigned int, DemoComponent>::iterator it = sceneData.TestComponents.begin(); it != sceneData.TestComponents.end(); ++it)
		{
			if ((*it).second.GetId() == id)
			{
				return true;
			}
		}
		return false;
	}

}
