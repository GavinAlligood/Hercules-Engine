#include "hcpch.h"

#include "Square.h"

Hercules::Square::Square()
{
	glGenVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);

	float vertices[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	//Binds automatically
	VertexBuffer vb(sizeof(vertices), vertices);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

	unsigned int indices[] = { 0, 1, 3,
							  1, 2, 3 };

	IndexBuffer ib(sizeof(indices), indices);

	vertexPath = "C:/Users/Gavin/source/repos/HerculesEngine/Hercules/Hercules0.1/src/Hercules/Shaders/Vertex.shader";
	fragmentPath = "C:/Users/Gavin/source/repos/HerculesEngine/Hercules/Hercules0.1/src/Hercules/Shaders/Fragment.shader";

	shader = new Shader(vertexPath, fragmentPath);

	shader->Bind();
	shader->SetColor(HC_GREEN);
}

Hercules::Square::~Square()
{
	delete shader;
}

void Hercules::Square::Draw()
{
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void Hercules::Square::Update()
{
	shader->Bind();
}
