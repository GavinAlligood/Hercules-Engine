#include "hcpch.h"

#include "Square.h"

Hercules::Square::Square()
{
	glGenVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);

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

	vertexPath = "C:/Users/Gavin/source/repos/HerculesEngine/Hercules/Hercules0.1/src/Hercules/Shaders/Vertex.shader";
	fragmentPath = "C:/Users/Gavin/source/repos/HerculesEngine/Hercules/Hercules0.1/src/Hercules/Shaders/Fragment.shader";

	shader = new Shader(vertexPath, fragmentPath);

	Texture texture(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR,
		"C:/Users/Gavin/source/repos/HerculesEngine/Hercules/Sandbox/Assets/EyeofSauronPixel.png", GL_RGB, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	shader->Bind();
	//shader->SetColor(HC_GREEN);
	shader->SetTexture(0);

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
