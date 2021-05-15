#pragma once

namespace Hercules {
	class VertexBuffer {
	public:
		VertexBuffer(unsigned int size, void* data);

		void Bind();
	private:
		unsigned int m_ID;
	};
}