#pragma once

#include "Component.h"

namespace Hercules {
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