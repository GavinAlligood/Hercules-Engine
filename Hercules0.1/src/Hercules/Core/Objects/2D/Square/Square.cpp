#include "hcpch.h"

#include "Square.h"

namespace Hercules {

	unsigned int SquareArray;

	void Hercules::Square::Init()
	{
		glGenVertexArrays(1, &SquareArray);
		glBindVertexArray(SquareArray);

		float vertices[] = {  ///texture
			1.0f, 1.0f, 0.0f,   1.0f, 1.0f,
			1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			-1.0f, 1.0f, 0.0f,  0.0f, 1.0f
		};

		//Binds automatically
		VertexBuffer vb(sizeof(vertices), vertices);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		unsigned int indices[] = { 0, 1, 3,
								  1, 2, 3 };

		IndexBuffer ib(sizeof(indices), indices);
	}

	void Hercules::Square::Draw(Texture& texture,
		glm::vec2 pos, glm::vec3 scale, glm::vec3 rotation, glm::vec3 color,
		Shader* shader)
	{
		//texture.Bind();
		glBindVertexArray(SquareArray);
		shader->Bind();
		shader->SetColor(color.x, color.y, color.z, 1.0f);
		shader->SetBool("mode", false);

		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(pos, 0.0f));
		trans = glm::translate(trans, glm::vec3(0.5f * scale.x, 0.5f * scale.y, 0.0f));
		trans = glm::rotate(trans, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::translate(trans, glm::vec3(-0.5f * scale.x, -0.5f * scale.y, 0.0f));
		trans = glm::scale(trans, scale);

		shader->SetMat4("transform", trans);

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

		shader->SetMat4("projection", projection);


		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}