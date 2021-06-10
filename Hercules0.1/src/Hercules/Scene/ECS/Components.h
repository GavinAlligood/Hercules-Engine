#pragma once

#include "hcpch.h"
#include <glm/glm.hpp>

namespace Hercules {

	enum class ComponentType
	{
		Test,
		Mesh,
		Transform
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
		TransformComponent(unsigned int id, glm::vec3 pos)
			: m_ID(id), m_Pos(pos) {};
		~TransformComponent() {};

		inline unsigned int GetId() const override { return m_ID; }
		inline glm::vec3 GetPos() { return m_Pos; }
		inline void SetPos(glm::vec3 pos) { m_Pos = pos; }

		ComponentType GetType() const override { return ComponentType::Transform; }
	private:
		unsigned int m_ID;

		glm::vec3 m_Pos = glm::vec3(0.0f);
	};
}