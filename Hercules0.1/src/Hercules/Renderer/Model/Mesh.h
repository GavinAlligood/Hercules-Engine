#pragma once

#include "glm/glm.hpp"
#include "../GL/Shader/Shader.h"
#include "Hercules/Renderer/GL/Texture/Texture.h"
#include "Hercules/Renderer/GL/Vertex/VertexBuffer.h"
#include "Hercules/Renderer/GL/Index/IndexBuffer.h"
#include "Hercules/Scene/Camera/Camera.h"

namespace Hercules {
	struct MeshVertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
		// tangent
		glm::vec3 Tangent;
		// bitangent
		glm::vec3 Bitangent;
	};

	/*struct MeshTexture {
		unsigned int id;
		std::string type;
		std::string path;
	};*/

	class Mesh {
	public:
		Mesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices); //std::vector<MeshTexture> textures

		std::vector<MeshVertex> vertices;
		std::vector<unsigned int> indices;
		//std::vector<MeshTexture> textures;

		void Draw(Texture& texture, glm::vec3& pos, glm::vec3& scale,
			glm::vec3& rotation, Shader* shader);

	private:
		unsigned int VAO, VBO, EBO;

		void setupMesh();
	};
}
