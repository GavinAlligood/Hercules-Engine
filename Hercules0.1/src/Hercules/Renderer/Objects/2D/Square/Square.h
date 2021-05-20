#pragma once

#include <glad/glad.h>

#include "Hercules/Renderer/Shader/Shader.h"
#include "Hercules/Renderer/Vertex/VertexBuffer.h"
#include "Hercules/Renderer/Index/IndexBuffer.h"

namespace Hercules {
	class Square {
	public:
		Square();
		~Square();

		void Draw();
		void Update();
	private:
		Shader* shader = nullptr;
		unsigned int m_VertexArray;
		std::string vertexPath, fragmentPath;
	};
}