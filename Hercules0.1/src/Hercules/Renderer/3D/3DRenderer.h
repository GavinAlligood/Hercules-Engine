#pragma once

#include "Hercules/Core/Objects/3D/Cube/Cube.h"

#include "Hercules/Scene/GL/Texture/Texture.h"

namespace Hercules {
	class SpatialRenderer {
	public:
		SpatialRenderer();
		~SpatialRenderer();

		void DrawCube(Texture defaultText,
			glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation,
			glm::vec4 color);
	private:
		Cube* cube = nullptr;
	};
}