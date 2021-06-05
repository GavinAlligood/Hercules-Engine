#pragma once

#include "Hercules/Scene/GL/Shader/Shader.h"
#include "Hercules/Scene/GL/Texture/Texture.h"
#include "Hercules/Scene/GL/Vertex/VertexBuffer.h"

namespace Hercules {

	class Renderer {
	public:
		Renderer();
		~Renderer();

		static void Init()
		{
			Shader shader("Assets/Shaders/Vertex.shader",
				"Assets/Shaders/Fragment.shader");
		}
		
	private:
		static Shader shader;
	};

}