#include "hcpch.h"

#include "2DRenderer.h"

Hercules::FlatRenderer::FlatRenderer()
{	
	square = new Square();
}

Hercules::FlatRenderer::~FlatRenderer()
{
	delete square;
}

void Hercules::FlatRenderer::DrawSquare(Texture defaultText,
	glm::vec2 pos, glm::vec3 scale, glm::vec3 rotation,
	glm::vec4 color)
{
	//default settings
	defaultText.Bind();
	square->Draw(defaultText, pos, scale, rotation, color);
}

void Hercules::FlatRenderer::DrawTriangle()
{
}
