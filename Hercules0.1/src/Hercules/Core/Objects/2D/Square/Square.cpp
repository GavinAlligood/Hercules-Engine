#include "hcpch.h"

#include "Square.h"

Hercules::Square::Square()
{
}

Hercules::Square::~Square()
{
}

//Theres no way doing this every frame is good for performance but ill worry
//about that later
void Hercules::Square::Draw(Texture& texture, glm::vec3 pos, glm::vec3 scale,
	float deg, glm::vec3 rotation, glm::vec3 color)
{
	float vertices[] = {  ///texture
		0.5f, 0.5f, 0.0f,   1.0f, 1.0f,
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,  0.0f, 1.0f
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

	Shader shader("Assets/Shaders/Vertex.shader",
		"Assets/Shaders/Fragment.shader");

	shader.Bind();
	shader.SetColor(color.x, color.y, color.z, 1.0f);
	shader.SetBool("mode", false);

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, pos);
	trans = glm::scale(trans, scale);
	trans = glm::rotate(trans, glm::radians(deg), rotation);
	
	shader.SetMat4("transform", trans);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}