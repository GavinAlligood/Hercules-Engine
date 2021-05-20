#pragma once

#include <string>

namespace Hercules {
	class Shader
	{
	public:
		Shader(std::string vertexPath, std::string fragmentPath);
		~Shader();

		void Bind() const;
		
		void SetColor(float v0, float v1, float v2, float v3);
	private:
		unsigned int m_ID;
	};
}

#define HC_RED 1.0f, 0.0f, 0.0f, 1.0f
#define HC_BLUE 0.0f, 0.0f, 1.0f, 1.0f
#define HC_GREEN 0.0f, 1.0f, 0.0f, 1.0f