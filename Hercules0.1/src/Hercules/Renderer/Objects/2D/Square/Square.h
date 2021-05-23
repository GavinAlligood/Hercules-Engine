#pragma once

#include <glad/glad.h>
#include "Hercules/Renderer/stbi/stb_image.h"

#include "Hercules/Renderer/Shader/Shader.h"
#include "Hercules/Renderer/Vertex/VertexBuffer.h"
#include "Hercules/Renderer/Index/IndexBuffer.h"

#include "Hercules/Renderer/Texture/Texture.h"

namespace Hercules {
	class Square {
	public:
		Square();
		~Square();

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

#define HC_IMG_PNG 1
#define HC_IMG_JPG 0