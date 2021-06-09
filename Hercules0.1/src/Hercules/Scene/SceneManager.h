#pragma once

#include "Hercules/Scene/ECS/Components.h"

namespace Hercules {
	class SceneManager {
	public:
		SceneManager() {};
		~SceneManager() {};

		static void AppendComponent(unsigned int key, Component& c);

		static bool GetDemoComponent(unsigned int id);
		static bool GetMeshComponent(unsigned int id);
		
		static std::map<unsigned int, DemoComponent> GetDemoComponents();
		static std::map<unsigned int, MeshComponent> GetMeshComponents();
	};

	struct SceneData {
		std::map<unsigned int, DemoComponent> TestComponents;
		std::map<unsigned int, MeshComponent> MeshComponents;
	};
}