#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Hercules/Renderer/GL/Texture/Texture.h"

#include "Hercules/Scene/Camera/Camera.h"

#include "Hercules/Renderer/Model/Model.h"

namespace Hercules {
	class SpatialRenderer {
	public:
		SpatialRenderer() {};
		~SpatialRenderer() {};

		static void WindowResize(int width, int height);

		static const void ClearColorBuffer(glm::vec3 color);
		static const void ClearColorBuffer(float r, float g, float b);

		static void DrawMesh(Model& model, Texture& defaultText,
			glm::vec3& pos, glm::vec3& scale, glm::vec3& rotation,
			Shader* shader);
	};
}