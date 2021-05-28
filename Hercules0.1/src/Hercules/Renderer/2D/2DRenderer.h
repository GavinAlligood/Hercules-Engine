#pragma once

#include "Hercules/Core/Objects/2D/Square/Square.h"
#include "Hercules/Core/Objects/2D/Triangle/Triangle.h"

#include "Hercules/Scene/GL/Texture/Texture.h"

namespace Hercules {
	class FlatRenderer {
	public:
		FlatRenderer();
		~FlatRenderer();

		void DrawSquare(Texture defaultText);
		void DrawTriangle();
	private:
		Square* square = nullptr;
	};
}