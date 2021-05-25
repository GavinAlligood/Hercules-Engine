#pragma once

#include <glad/glad.h>

#include "Hercules/Scene/GL/Shader/Shader.h"
#include "Hercules/Scene/GL/Vertex/VertexBuffer.h"
#include "Hercules/Scene/GL/Index/IndexBuffer.h"

#include "Hercules/Scene/GL/Texture/Texture.h"

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