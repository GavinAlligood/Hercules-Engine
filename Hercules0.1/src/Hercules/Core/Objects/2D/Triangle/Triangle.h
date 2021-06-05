#pragma once

#include <glad/glad.h>

#include "Hercules/Renderer/GL/Shader/Shader.h"
#include "Hercules/Renderer/GL/Vertex/VertexBuffer.h"
#include "Hercules/Renderer/GL/Index/IndexBuffer.h"

#include "Hercules/Renderer/GL/Texture/Texture.h"

namespace Hercules {
	class Triangle {
	public:
		Triangle();
		~Triangle();

		void Draw();
		void Update();

		void SetTexture(const char* path, bool type);
		void SetColor(float r, float g, float b, float a);
	private:
		Shader* shader = nullptr;
		unsigned int m_VertexArray;
		std::string vertexPath, fragmentPath;
	};
}