#include "hcpch.h"

#include "VertexArray.h"

#include <glad/glad.h>

Hercules::VAO::VAO()
{
	glGenVertexArrays(1, &m_ID);
	glBindVertexArray(m_ID);
}

Hercules::VAO::~VAO()
{
	glDeleteVertexArrays(1, &m_ID);
}

void Hercules::VAO::Bind() const
{
	glBindVertexArray(m_ID);
}
