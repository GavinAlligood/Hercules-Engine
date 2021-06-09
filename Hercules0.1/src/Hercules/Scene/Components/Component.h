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
}