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
	};
}