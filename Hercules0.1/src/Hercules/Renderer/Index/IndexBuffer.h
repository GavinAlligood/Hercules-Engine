#pragma once

#include "Hercules/Application/Core.h"

namespace Hercules {
	class HERCULES_API IBO {
	public:
		IBO(const unsigned int* data, unsigned int count);
		~IBO();

		void Bind() const;

		inline unsigned int GetCount() const { return m_Count; }
	private:
		unsigned int m_ID;
		unsigned int m_Count;
	};
}