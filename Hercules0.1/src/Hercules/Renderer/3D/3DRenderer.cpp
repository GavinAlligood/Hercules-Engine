#include "hcpch.h"

#include "3DRenderer.h"

Hercules::SpatialRenderer::SpatialRenderer()
{
	cube = new Cube();
}

Hercules::SpatialRenderer::~SpatialRenderer()
{
	delete cube;
}

void Hercules::SpatialRenderer::DrawCube(Texture defaultText)
{
	defaultText.Bind();

	cube->Draw(defaultText, glm::vec3(0.0f, 0.0f, -5.0f), 
		glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f), 
		glm::vec3(0.0f, 1.0f, 0.0f));
}
