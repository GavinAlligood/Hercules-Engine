#pragma once

#include "Hercules/Scene/ECS/Components.h"

namespace Hercules {
	class SceneManager {
	public:
		SceneManager() {};
		~SceneManager() {};

		static void PrintStats();

		static void NewComponent(Component& c, unsigned int id);
		static void NewEntity(std::string name);
		static void DeleteComponent(ComponentType c, unsigned int id);
		static void DeleteEntity(unsigned int id);

		static DemoComponent* GetDemoComponent(unsigned int id);
		static MeshComponent* GetMeshComponent(unsigned int id);
		static TransformComponent* GetTransformComponent(unsigned int id);
		static LightComponent* GetLightComponent(unsigned int id);
		static DirectionalLight* GetDirectionalLightComponent(unsigned int id);
		static PointLight* GetPointLightComponent(unsigned int id);
		static SpotLight* GetSpotLightComponent(unsigned int id);
		static MaterialComponent* GetMaterialComponent(unsigned int id);

		//maybe make this one "HasComponent(ComponentType, uint32 id)"
		static bool HasLightComponent(unsigned int id);
		static bool HasDirectionalLight(unsigned int id);
		static bool HasPointLight(unsigned int id);
		static bool HasSpotLight(unsigned int id);
		static bool HasTransformComponent(unsigned int id);
		static bool HasTestComponent(unsigned int id);
		static bool HasMaterialComponent(unsigned int id);

		static std::map<unsigned int, DemoComponent> &GetDemoComponentList();
		static std::map<unsigned int, MeshComponent> &GetMeshComponentList();
		static std::map<unsigned int, TransformComponent> &GetTransformComponentList();
		static std::map<unsigned int, LightComponent> &GetLightComponentList();
		static std::map<unsigned int, DirectionalLight>& GetDirectionalLightList();
		static std::map<unsigned int, PointLight>& GetPointLightList();
		static std::map<unsigned int, SpotLight>& GetSpotLightList();
		static std::map<unsigned int, MaterialComponent>& GetMaterialComponentList();

		static std::map<unsigned int, std::string>& GetEntites();

		//Textures
		static void NewTexture(std::string name, const char* path);
		static Texture* GetTexture(const char* name);
		static std::map<std::string, Texture>& GetTextureList();

		static const glm::vec3 GetBackgroundColor();
		static void SetBackgroundColor(glm::vec3 color);
		static void SetBackgroundColor(float r, float g, float b);
	};

	struct SceneData {
		std::map<unsigned int, DemoComponent> TestComponents;
		std::map<unsigned int, MeshComponent> MeshComponents;
		std::map<unsigned int, TransformComponent> TransformComponents;
		std::map<unsigned int, LightComponent> LightComponents;
		std::map<unsigned int, DirectionalLight> DirectionalLightComponents;
		std::map<unsigned int, PointLight> PointLightComponents;
		std::map<unsigned int, SpotLight> SpotLightComponents;
		std::map<unsigned int, MaterialComponent> MaterialComponents;

		std::map<unsigned int, std::string> Entities;

		//Textures
		std::map<std::string, Texture> textures;

		glm::vec3 BackgroundColor = glm::vec3(0.0f);
	};
}