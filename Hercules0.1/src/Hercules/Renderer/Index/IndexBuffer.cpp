#include "hcpch.h"

#include "IndexBuffer.h"

#include <glad/glad.h>

Hercules::IBO::IBO(const unsigned int* data, unsigned int count)
    : m_Count(count)
{
    glGenBuffers(1, &m_ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, data, GL_STATIC_DRAW);
}

Hercules::IBO::~IBO()
{
    glDeleteBuffers(1, &m_ID);
}

void Hercules::IBO::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}
