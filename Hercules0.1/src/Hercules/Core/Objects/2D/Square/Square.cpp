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

	vertexPath = "Assets/Shaders/Vertex.shader";
	fragmentPath = "Assets/Shaders/Fragment.shader";

	shader = new Shader(vertexPath, fragmentPath);

	shader->Bind();
	//TODO: change this to shader->UseColor for readability
	shader->SetBool("UseColor", false);
	//shader->SetColor(HC_GREEN);
	//shader->SetTexture(0);
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
	glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

	shader->Bind();

	unsigned int transformLoc = glGetUniformLocation(shader->GetId(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
}

////Different than SetTexture in shader
//void Hercules::Square::SetTexture(const char* path, bool type)
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

void Hercules::Square::SetColor(float r, float g, float b, float a)
{
	shader->SetColor(r, g, b, a);
}
