#pragma once

#include "Hercules/Scene/ECS/Components.h"

namespace Hercules {
	class SceneManager {
	public:
		SceneManager() {};
		~SceneManager() {};

		static void PrintStats();

		static void AppendComponent(unsigned int key, Component& c);

		static bool GetDemoComponent(unsigned int id);
		static bool GetMeshComponent(unsigned int id);
		//static bool GetTransformComponent(unsigned int id);

		static std::map<unsigned int, TransformComponent>::iterator GetTransformComponent(unsigned int key);

		static std::map<unsigned int, DemoComponent> GetDemoComponentList();
		static std::map<unsigned int, MeshComponent> GetMeshComponentList();
		static std::map<unsigned int, TransformComponent> &GetTransformComponentList();
	};

	struct SceneData {
		std::map<unsigned int, DemoComponent> TestComponents;
		std::map<unsigned int, MeshComponent> MeshComponents;
		std::map<unsigned int, TransformComponent> TransformComponents;
	};
}