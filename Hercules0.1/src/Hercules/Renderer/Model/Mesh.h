#pragma once

#include "glm/glm.hpp"
#include "../GL/Shader/Shader.h"
#include "Hercules/Renderer/GL/Texture/Texture.h"
#include "Hercules/Renderer/GL/Vertex/VertexBuffer.h"
#include "Hercules/Renderer/GL/Index/IndexBuffer.h"

namespace Hercules {
	struct MeshVertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	struct MeshTexture {
		unsigned int id;
		std::string type;
		std::string path;
	};

	class Mesh {
	public:
		Mesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices, MeshTexture texture);

		std::vector<MeshVertex> vertices;
		std::vector<unsigned int> indices;
		MeshTexture texture;

		void Draw(Shader& shader);

	private:
		unsigned int VAO, VBO, EBO;

		void setupMesh();
	};
}
