#include "hcpch.h"

#include "Renderer.h"

#include <glad/glad.h>

Hercules::Renderer::Renderer(VBO vb, VAO va, IBO ib, Shader sh)
	: vbo(vb), vao(va), ibo(ib), shader(sh)
{
	HC_INFO("Starting renderer");
}

Hercules::Renderer::~Renderer()
{
}

void Hercules::Renderer::Draw()
{
	shader.Use();
	vao.Bind();
	glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, 0);
}

void Hercules::Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}
