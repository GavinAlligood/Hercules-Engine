#pragma once

#include "hcpch.h"

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
}