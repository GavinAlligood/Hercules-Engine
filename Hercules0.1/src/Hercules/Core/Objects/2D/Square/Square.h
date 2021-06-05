#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Hercules/Renderer/GL/Shader/Shader.h"
#include "Hercules/Renderer/GL/Vertex/VertexBuffer.h"
#include "Hercules/Renderer/GL/Index/IndexBuffer.h"

#include "Hercules/Renderer/GL/Texture/Texture.h"

namespace Hercules {
	class Square {
	public:
		Square();
		~Square();

		void Draw(Texture& texture, glm::vec2 pos,
			glm::vec3 scale, glm::vec3 rotation, glm::vec3 color);
	};
}