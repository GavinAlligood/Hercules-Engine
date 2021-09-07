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

void Hercules::Mesh::Draw(Texture& texture, glm::vec3& pos, glm::vec3& scale,
	glm::vec3& rotation, Shader* shader)
{
	texture.Bind();

	glBindVertexArray(VAO);

	shader->Bind();

	shader->SetBool("mode", true);

	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, pos);
	model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, scale);

	shader->SetMat4("model", model);

	glm::mat4 projection = Camera::GetProjectionMatrix();
	glm::mat4 view;
	view = glm::lookAt(Camera::GetPos(), Camera::GetPos() + Camera::GetFront(), Camera::GetUp());
	shader->SetMat4("projection", projection);
	shader->SetMat4("view", view);

	shader->SetMat3("normalCalc", glm::mat3(glm::transpose(glm::inverse(model))));

	//glDrawArrays(GL_TRIANGLES, 0, 32);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Hercules::Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VertexBuffer vb(vertices.size() * sizeof(MeshVertex), &vertices[0]);
	IndexBuffer ib(indices.size() * sizeof(unsigned int), &indices[0]);

	//vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, TexCoords));
	// vertex tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, Tangent));
	// vertex bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, Bitangent));

	glBindVertexArray(0);
}
