#pragma once

#include <string>

namespace Hercules {
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
	private:
		unsigned int m_ID;
	};
}