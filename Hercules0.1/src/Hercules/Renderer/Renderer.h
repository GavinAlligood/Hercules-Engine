#pragma once

#include "Hercules/Application/Core.h"

#include "Vertex/VertexArray.h"
#include "Vertex/VertexBuffer.h"
#include "Index/IndexBuffer.h"
#include "Shader/Shader.h"

namespace Hercules {
	class HERCULES_API Renderer
	{
	public:
		Renderer(VBO vb, VAO va, IBO ib, Shader sh);
		~Renderer();

		void Draw();
		void Clear() const;
	private:
		VAO vao;
		VBO vbo;
		IBO ibo;
		Shader shader;
	};
}