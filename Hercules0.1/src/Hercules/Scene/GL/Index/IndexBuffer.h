#pragma once

namespace Hercules {
	class IndexBuffer {
	public:
		IndexBuffer(unsigned int size, void* data);

		void Bind() const;
	private:
		unsigned int m_ID;
	};
}