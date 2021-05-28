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

void Hercules::FlatRenderer::DrawSquare(Texture defaultText)
{
	//default settings
	defaultText.Bind();
	square->Draw(defaultText, glm::vec3(0.0, 0.0, 0.0),
		glm::vec3(0.5f, 0.8f, 0.5f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
}

void Hercules::FlatRenderer::DrawTriangle()
{
}
