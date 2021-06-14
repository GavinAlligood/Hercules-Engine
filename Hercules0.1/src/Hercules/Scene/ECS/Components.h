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
		Light
	};

	class Component {
	public:
		virtual ComponentType GetType() const = 0;

		inline virtual unsigned int GetId() const { return m_ID; }
	private:
		unsigned int m_ID;
	};

	class DemoComponent : public Component {
	public:
		DemoComponent(unsigned int id)
			: m_ID(id) {};
		~DemoComponent() {};

		inline unsigned int GetId() const override { return m_ID; }

		ComponentType GetType() const override { return ComponentType::Test; }
	private:
		unsigned int m_ID;
	};

	class MeshComponent : public Component {
	public:
		MeshComponent(unsigned int id)
			: m_ID(id) {};
		~MeshComponent() {};

		inline unsigned int GetId() const override { return m_ID; }

		ComponentType GetType() const override { return ComponentType::Mesh; }
	private:
		unsigned int m_ID;
	};

	class TransformComponent : public Component {
	public:
		TransformComponent(unsigned int id, 
			glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation, Texture& texture, glm::vec4 color)
			: m_ID(id), m_Pos(pos), m_Scale(scale), m_Rotation(rotation), m_Texture(texture), m_Color(color) {};
		~TransformComponent() {};

		inline unsigned int GetId() const override { return m_ID; }

		inline glm::vec3 GetPos() { return m_Pos; }
		inline glm::vec3 GetScale() { return m_Scale; }
		inline glm::vec3 GetRotation() { return m_Rotation; }
		inline glm::vec4 GetColor() { return m_Color; }

		inline Texture GetTexture() const { return m_Texture; }

		inline void SetPos(glm::vec3 pos) { m_Pos = pos; }
		inline void SetScale(glm::vec3 scale) { m_Scale = scale; }
		inline void SetRotation(glm::vec3 rotation) { m_Rotation = rotation; }
		inline void SetColor(glm::vec4 color) { m_Color = color; }

		ComponentType GetType() const override { return ComponentType::Transform; }
	private:
		unsigned int m_ID;

		glm::vec3 m_Pos = glm::vec3(0.0f);
		glm::vec3 m_Scale = glm::vec3(1.0f);
		glm::vec3 m_Rotation = glm::vec3(0.0f);
		glm::vec4 m_Color = glm::vec4(1.0f); //white by default, which wont show up for textures. so essentially just the default texture

		Texture& m_Texture;
	};

	class LightComponent : public Component {
	public:
		LightComponent(unsigned int id, glm::vec3 color)
			: m_ID(id), m_LightColor(color) {};
		~LightComponent() {};

		inline unsigned int GetId() const override { return m_ID; }

		inline glm::vec3 GetColor() { return m_LightColor; }

		inline void SetColor(glm::vec3 color) { m_LightColor = color; }

		ComponentType GetType() const override { return ComponentType::Light; }
	private:
		unsigned int m_ID;

		glm::vec3 m_LightColor = glm::vec3(1.0f);
	};
}