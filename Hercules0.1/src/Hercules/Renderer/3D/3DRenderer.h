#pragma once

#include "Hercules/Core/Objects/3D/Cube/Cube.h"
#include "Hercules/Core/Objects/3D/Test/Test.h"

#include "Hercules/Scene/GL/Texture/Texture.h"

#include "Hercules/Scene/Camera/Camera.h"

namespace Hercules {
	class SpatialRenderer {
	public:
		SpatialRenderer();
		~SpatialRenderer();

		void DrawCube(Texture defaultText,
			glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation,
			glm::vec4 color,
			glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);

		void DrawTest(Texture defaultText,
			glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation,
			glm::vec4 color,
			glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);
	private:
		Test* test = nullptr;
		Cube* cube = nullptr;
	};
}