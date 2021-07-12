#pragma once

#include "hcpch.h"
#include <glm/glm.hpp>
#include "Hercules/Renderer/GL/Texture/Texture.h"

namespace Hercules {

	enum class ComponentType
	{
		Test,
		Mesh,
		Transform,
		Material,
		Light, SpotLight, DirectionalLight, PointLight
	};

	class Component {
	public:
		virtual ComponentType GetType() const = 0;
	};

	class DemoComponent : public Component {
	public:
		DemoComponent() {};
	   ~DemoComponent() {};

		ComponentType GetType() const override { return ComponentType::Test; }
	};

	class MeshComponent : public Component {
	public:
		MeshComponent() {};
		~MeshComponent() {};

		ComponentType GetType() const override { return ComponentType::Mesh; }
	};

	class TransformComponent : public Component {
	public:
		TransformComponent( 
			glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation, Texture& texture, glm::vec4 color)
			: m_Pos(pos), m_Scale(scale), m_Rotation(rotation), m_Texture(texture) {}; // m_Texture(texture), m_Color(color)
		~TransformComponent() {};

		inline glm::vec3 GetPos() { return m_Pos; }
		inline glm::vec3 GetScale() { return m_Scale; }
		inline glm::vec3 GetRotation() { return m_Rotation; }

		inline Texture GetTexture() const { return m_Texture; }

		inline void SetPos(glm::vec3 pos) { m_Pos = pos; }
		inline void SetScale(glm::vec3 scale) { m_Scale = scale; }
		inline void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; }
	
		ComponentType GetType() const override { return ComponentType::Transform; }
	private:
		glm::vec3 m_Pos = glm::vec3(0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f);
		
		Texture& m_Texture;
	};

	class MaterialComponent : public Component {
	public:
		MaterialComponent(Texture* texture)
			: m_Texture(texture) {};
		~MaterialComponent() {};

		inline Texture* GetTexture() const { return m_Texture; }
		inline void SetTexture(Texture* tex) { m_Texture = tex; }
		
		inline glm::vec3 GetColor() { return m_Color; }
		inline float GetShininess() { return m_Shininess; }

		inline void SetColor(glm::vec3 color) { m_Color = color; }
		inline void SetShininess(float shiny) { m_Shininess = shiny; }

		ComponentType GetType() const override { return ComponentType::Material; }
	private:
		glm::vec3 m_Color = glm::vec3(1.0f);
		float m_Shininess = 32.0f;

		Texture* m_Texture;
	};

	class LightComponent : public Component {
	public:
		LightComponent() {};
		~LightComponent() {};

		virtual inline glm::vec3 GetColor() { return m_LightColor; }

		virtual inline void SetColor(glm::vec3 color) { m_LightColor = color; }
		virtual inline glm::vec3 GetDirection() { return m_Direction; }

		virtual inline float GetAmbient() { return m_Ambient; }
		virtual inline void SetAmbient(float ambient) { m_Ambient = ambient; }

		virtual ComponentType GetType() const override { return ComponentType::Light; }
	private:
		glm::vec3 m_LightColor = glm::vec3(1.0f);
		glm::vec3 m_Direction = glm::vec3(0.0f);

		float m_Ambient = 0.2f;
	};

	class DirectionalLight : public LightComponent {
	public:
		DirectionalLight() {};
		~DirectionalLight() {};

		virtual inline glm::vec3 GetColor() { return m_LightColor; }

		virtual inline void SetColor(glm::vec3 color) { m_LightColor = color; }

		ComponentType GetType() const override { return ComponentType::DirectionalLight; }
	private:
		glm::vec3 m_Direction = glm::vec3(0.0f);
		glm::vec3 m_LightColor = glm::vec3(1.0f);
	};

	class SpotLight : public LightComponent {
	public:
		SpotLight() {};
		~SpotLight() {};

		virtual inline glm::vec3 GetColor() { return m_LightColor; }

		virtual inline void SetColor(glm::vec3 color) { m_LightColor = color; }
		virtual inline glm::vec3 GetDirection() { return m_Direction; }

		ComponentType GetType() const override { return ComponentType::SpotLight; }
	private:
		glm::vec3 m_Direction = glm::vec3(0.0f);
		glm::vec3 m_LightColor = glm::vec3(1.0f);
	};

	class PointLight : public LightComponent {
	public:
		PointLight() {};
		~PointLight() {};

		virtual inline glm::vec3 GetColor() { return m_LightColor; }

		virtual inline void SetColor(glm::vec3 color) { m_LightColor = color; }

		ComponentType GetType() const override { return ComponentType::PointLight; }
	private:
		glm::vec3 m_LightColor = glm::vec3(1.0f);
	};
}