#pragma once

#include "Hercules/Application/Core.h"

#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

namespace Hercules {
	class HERCULES_API VAO
	{
	public:
		VAO();
		~VAO();

		void Bind() const;
		//void AddBuffer(const VBO& vb, const VBL& layout);
	private:
		unsigned int m_ID;
	};
}