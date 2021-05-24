#pragma once

#include <glad/glad.h>

#include "Hercules/Scene/GL/Shader/Shader.h"
#include "Hercules/Scene/GL/Vertex/VertexBuffer.h"
#include "Hercules/Scene/GL/Index/IndexBuffer.h"

namespace Hercules {
	class Triangle {
	public:
		Triangle();
		~Triangle();

		void Draw();
		void Update();
	private:
		Shader* shader = nullptr;
		unsigned int m_VertexArray;
		std::string vertexPath, fragmentPath;
	};
}