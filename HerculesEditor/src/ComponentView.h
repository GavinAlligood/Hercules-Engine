#pragma once

#include "Components/MaterialMenu.h"
#include "Components/LightMenu.h"
#include "Components/TransformMenu.h"
#include "Components/MeshMenu.h"

namespace Hercules {
	class ComponentView
	{
	public:
		ComponentView() {};
		~ComponentView() {};
		
		static void ConditionalRender();
	};
}