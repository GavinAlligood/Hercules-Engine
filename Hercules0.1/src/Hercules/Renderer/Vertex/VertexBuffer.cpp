#include "hcpch.h"

#include "VertexBuffer.h"

#include <glad/glad.h>

Hercules::VBO::VBO(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

Hercules::VBO::~VBO()
{
	glDeleteBuffers(1, &m_ID);
}

void Hercules::VBO::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}