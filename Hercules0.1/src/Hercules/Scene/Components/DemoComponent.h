#pragma once

#include "Component.h"

namespace Hercules {
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
}