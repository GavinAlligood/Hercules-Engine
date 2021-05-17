#include "hcpch.h"

#include "Cube.h"

Hercules::Cube::Cube()
{
	glGenVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);

	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	//Binds automatically
	VertexBuffer vb(sizeof(vertices), vertices);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	unsigned int indices[3] = { 0, 1, 2 };

	IndexBuffer ib(sizeof(indices), indices);

	vertexPath = "C:/Users/Gavin/source/repos/HerculesEngine/Hercules/Hercules0.1/src/Hercules/Shaders/Vertex.shader";
	fragmentPath = "C:/Users/Gavin/source/repos/HerculesEngine/Hercules/Hercules0.1/src/Hercules/Shaders/Fragment.shader";

	shader = new Shader(vertexPath, fragmentPath);
}

Hercules::Cube::~Cube()
{
	delete shader;
}

void Hercules::Cube::Draw()
{
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}

void Hercules::Cube::Update()
{
	shader->Bind();
}
