#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Hercules/Scene/GL/Shader/Shader.h"
#include "Hercules/Scene/GL/Vertex/VertexBuffer.h"
#include "Hercules/Scene/GL/Index/IndexBuffer.h"

#include "Hercules/Scene/GL/Texture/Texture.h"

namespace Hercules {
	class Cube {
	public:
		Cube();
		~Cube();

		void Draw(Texture& texture, glm::vec3 pos, glm::vec3 scale,
			glm::vec3 rotation, glm::vec4 color,
			glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);
	private:
		Shader* shader = nullptr;
	};
}