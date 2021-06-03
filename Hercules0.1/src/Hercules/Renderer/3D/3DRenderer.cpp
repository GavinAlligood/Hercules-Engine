#include "hcpch.h"

#include "3DRenderer.h"

Hercules::SpatialRenderer::SpatialRenderer()
{
	glEnable(GL_DEPTH_TEST);
	cube = new Cube();
	test = new Test();
}

Hercules::SpatialRenderer::~SpatialRenderer()
{
	delete cube;
	delete test;
}

void Hercules::SpatialRenderer::DrawCube(Texture defaultText,
	glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation,
	glm::vec4 color,
	glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp)
{
	defaultText.Bind();

	cube->Draw(defaultText, pos, scale, rotation, color, cameraPos, 
		cameraFront, cameraUp);
}

void Hercules::SpatialRenderer::DrawTest(Texture defaultText,
	glm::vec3 pos, glm::vec3 scale, glm::vec3 rotation, 
	glm::vec4 color,
	glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp)
{
	defaultText.Bind();

	test->Draw(defaultText, pos, scale, rotation, color, cameraPos,
		cameraFront, cameraUp);
}
