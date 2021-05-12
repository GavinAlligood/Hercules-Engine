#pragma once

#include "Hercules/Application/Core.h"

namespace Hercules {
	class HERCULES_API VBO {
	public:
		VBO(const void* data, unsigned int size);
		~VBO();

		void Bind() const;
	private:
		unsigned int m_ID;
	};
}