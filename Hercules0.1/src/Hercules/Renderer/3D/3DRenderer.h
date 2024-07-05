#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "Hercules/Renderer/GL/Texture/Texture.h"

#include "Hercules/Scene/Camera/Camera.h"

#include "Hercules/Renderer/Model/Model.h"

//This class can just be static i.e only containing static functions.
//Nothing is really being 'stored' here so there's no need to make this a Singleton

namespace Hercules {
	class SpatialRenderer {
	public:

		//TODO: Delete operators

		

		static void WindowResize(int width, int height);

		static const void ClearColorBuffer(glm::vec3 color);
		static const void ClearColorBuffer(float r, float g, float b);

		static void DrawMesh(Model& model, Texture& defaultText,
			glm::vec3& pos, glm::vec3& scale, glm::vec3& rotation,
			Shader* shader);
	private:
		SpatialRenderer() {};
		~SpatialRenderer() {};
	};
}
