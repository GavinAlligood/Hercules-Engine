#include "hcpch.h"

#include "3DRenderer.h"

Hercules::SpatialRenderer::SpatialRenderer()
{
}

Hercules::SpatialRenderer::~SpatialRenderer()
{
}

void Hercules::SpatialRenderer::Init()
{
	glEnable(GL_DEPTH_TEST);

	Cube::Init();
	Test::Init();
}

void Hercules::SpatialRenderer::DrawCube(Texture defaultText,
	glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation,
	glm::vec4 color,
	glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp,
	Shader* shader)
{
	Cube::Draw(defaultText, pos, scale, rotation,
		color, cameraPos, cameraFront, cameraUp, shader);
}

void Hercules::SpatialRenderer::DrawTest(Texture defaultText,
	glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation, 
	glm::vec4 color,
	glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp,
	Shader* shader)
{
	Test::Draw(defaultText, pos, scale, rotation,
		color, cameraPos, cameraFront, cameraUp, shader);
}
