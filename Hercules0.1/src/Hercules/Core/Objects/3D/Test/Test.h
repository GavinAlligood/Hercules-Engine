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
	class Test {
	public:
		Test() {};
		~Test() {};

		static void Draw(Texture& texture, glm::vec3 pos, glm::vec3 scale,
			glm::vec3 rotation, glm::vec4 color,
			glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp,
			Shader* shader);

		static void Init();
	};
}