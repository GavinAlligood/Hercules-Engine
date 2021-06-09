#include "hcpch.h"

#include "Triangle.h"

Hercules::Triangle::Triangle()
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

	vertexPath = "Assets/Shaders/Vertex.shader";
	fragmentPath = "Assets/Shaders/Fragment.shader";

	shader = new Shader(vertexPath, fragmentPath);

	shader->Bind();

	shader->SetBool("UseColor", true);
}

Hercules::Triangle::~Triangle()
{
	delete shader;
}

void Hercules::Triangle::Draw()
{
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
}

void Hercules::Triangle::Update()
{
	shader->Bind();
}

//void Hercules::Triangle::SetTexture(const char* path, bool type)
//{
//	if (type == HC_IMG_PNG)
//	{
//		Texture texture(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR,
//			path, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE, 0);
//
//		shader->SetTexture(0);
//	}
//	else
//	{
//		Texture texture(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_LINEAR, GL_LINEAR,
//			path, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, 0);
//
//		shader->SetTexture(0);
//	}
//}

void Hercules::Triangle::SetColor(float r, float g, float b, float a)
{
	shader->SetColor(r, g, b, a);
}
