#include "hcpch.h"

#include "3DRenderer.h"

void Hercules::SpatialRenderer::WindowResize(int width, int height)
{
	glViewport(0, 0, width, height);
}

const void Hercules::SpatialRenderer::ClearColorBuffer(glm::vec3 color)
{
	glClearColor(color.x, color.y, color.z, 1);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

const void Hercules::SpatialRenderer::ClearColorBuffer(float r, float g, float b)
{
	glClearColor(r, g, b, 1);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void Hercules::SpatialRenderer::DrawMesh(Model& model,
	Texture& defaultText, glm::vec3& pos, glm::vec3& scale, glm::vec3& rotation, Shader* shader)
{
	glEnable(GL_DEPTH_TEST);
	model.Draw(defaultText, pos, scale, rotation, shader);
}