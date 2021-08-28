#include "hcpch.h"

#include "Mesh.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>


//TODO: use hercules textures

Hercules::Mesh::Mesh(std::vector<MeshVertex> vertices, std::vector<unsigned int> indices, MeshTexture texture)
{
	this->vertices = vertices;
	this->indices = indices;
	this->texture = texture;

	setupMesh();
}

void Hercules::Mesh::Draw(Shader& shader)
{
	//unsigned int diffuseNr = 1;
	//unsigned int specularNr = 1;
	//for (unsigned int i = 0; i < textures.size(); i++)
	//{
	//	glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
	//	// retrieve texture number (the N in diffuse_textureN)
	//	std::string number;
	//	std::string name = textures[i].type;
	//	if (name == "texture_diffuse")
	//		number = std::to_string(diffuseNr++);
	//	else if (name == "texture_specular")
	//		number = std::to_string(specularNr++);

	//	shader.SetFloat(("material." + name + number).c_str(), i);
	//	
	//}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.id);

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Hercules::Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	VertexBuffer vb(vertices.size() * sizeof(MeshVertex), &vertices[0]);
	IndexBuffer ib(indices.size() * sizeof(unsigned int), &indices[0]);

	glBindVertexArray(VAO);
	
	
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(MeshVertex), &vertices[0], GL_STATIC_DRAW);

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
		&indices[0], GL_STATIC_DRAW);*/

	//vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, TexCoords));

	glBindVertexArray(0);
}
