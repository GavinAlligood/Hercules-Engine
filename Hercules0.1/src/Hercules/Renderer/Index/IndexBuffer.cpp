#include "hcpch.h"

#include "IndexBuffer.h"

#include <glad/glad.h>

Hercules::IndexBuffer::IndexBuffer(unsigned int size, void* data)
{
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void Hercules::IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}
