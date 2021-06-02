#pragma once

#include "Hercules/Core/Objects/3D/Cube/Cube.h"

#include "Hercules/Scene/GL/Texture/Texture.h"

#include "Hercules/Scene/Camera/Camera.h"

namespace Hercules {
	class SpatialRenderer {
	public:
		SpatialRenderer(Camera* sceneCamera);
		~SpatialRenderer();

		void DrawCube(Texture defaultText,
			glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation,
			glm::vec4 color);
	private:
		Cube* cube = nullptr;

		Camera* m_SceneCamera;

		glm::vec3 cameraPos = *m_SceneCamera->GetPos();
		glm::vec3 cameraFront = *m_SceneCamera->GetFront();
		glm::vec3 cameraUp = *m_SceneCamera->GetUp();
	};
}