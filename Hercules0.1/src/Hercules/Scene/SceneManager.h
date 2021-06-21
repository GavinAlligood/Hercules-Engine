#pragma once

#include "Hercules/Scene/ECS/Components.h"

namespace Hercules {
	class SceneManager {
	public:
		SceneManager() {};
		~SceneManager() {};

		static void PrintStats();

		static void NewComponent(unsigned int key, Component& c);
		static void NewEntity(unsigned int id, const char* name);

		static DemoComponent* GetDemoComponent(unsigned int id);
		static MeshComponent* GetMeshComponent(unsigned int id);
		static TransformComponent* GetTransformComponent(unsigned int id);
		static LightComponent* GetLightComponent(unsigned int id);
		
		static bool HasLightComponent(unsigned int id);
		static bool HasTransformComponent(unsigned int id);

		static std::map<unsigned int, DemoComponent> &GetDemoComponentList();
		static std::map<unsigned int, MeshComponent> &GetMeshComponentList();
		static std::map<unsigned int, TransformComponent> &GetTransformComponentList();
		static std::map<unsigned int, LightComponent> &GetLightComponentList();

		static std::map<unsigned int, const char*>& GetEntites();
	};

	struct SceneData {
		std::map<unsigned int, DemoComponent> TestComponents;
		std::map<unsigned int, MeshComponent> MeshComponents;
		std::map<unsigned int, TransformComponent> TransformComponents;
		std::map<unsigned int, LightComponent> LightComponents;

		std::map<unsigned int, const char*> Entities;
	};
}