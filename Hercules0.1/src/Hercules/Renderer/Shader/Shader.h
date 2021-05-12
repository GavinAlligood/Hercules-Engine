#pragma once

#include "Hercules/Application/Core.h"

namespace Hercules {
	class HERCULES_API Shader
	{
	public:
		unsigned int ID;

		Shader(const char* vertexPath, const char* fragmentPath);

		void Use() const;
	};
}