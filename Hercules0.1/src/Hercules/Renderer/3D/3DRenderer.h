#pragma once

#include "Hercules/Core/Objects/3D/Cube/Cube.h"

#include "Hercules/Scene/GL/Texture/Texture.h"

namespace Hercules {
	class SpatialRenderer {
	public:
		SpatialRenderer();
		~SpatialRenderer();

		void DrawCube(Texture defaulText);
	private:
		Cube* cube = nullptr;
	};
}