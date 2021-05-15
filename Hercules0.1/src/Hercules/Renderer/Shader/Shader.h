#pragma once

#include <string>

namespace Hercules {
	class Shader
	{
	public:
		Shader(std::string vertexPath, std::string fragmentPath);
		~Shader();

		void Bind() const;
		
	private:
		unsigned int m_ID;
	};
}