#include "hcpch.h"

#include "VertexBuffer.h"

#include <glad/glad.h>

Hercules::VertexBuffer::VertexBuffer(unsigned int size, void* data)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);

	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Hercules::VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}
