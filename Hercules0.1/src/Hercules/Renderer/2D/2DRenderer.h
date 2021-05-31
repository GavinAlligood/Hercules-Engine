#pragma once

#include "Hercules/Core/Objects/2D/Square/Square.h"
#include "Hercules/Core/Objects/2D/Triangle/Triangle.h"

#include "Hercules/Scene/GL/Texture/Texture.h"

namespace Hercules {
	class FlatRenderer {
	public:
		FlatRenderer();
		~FlatRenderer();

		void DrawSquare(Texture defaultText,
			glm::vec2 pos, glm::vec3 scale, glm::vec3 rotation,
			glm::vec4 color);
		void DrawTriangle();
	private:
		Square* square = nullptr;
	};
}