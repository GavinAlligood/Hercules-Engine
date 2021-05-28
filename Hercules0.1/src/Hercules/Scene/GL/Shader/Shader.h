#pragma once

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Hercules {
	class Shader
	{
	public:
		Shader(std::string vertexPath, std::string fragmentPath);
		~Shader();

		void Bind() const;
		
		void SetColor(float v0, float v1, float v2, float v3);
		void SetTexture(unsigned int id);

		void SetBool(const char* name, bool b);

		void SetMat4(const char* name, glm::mat4 m);

		const inline unsigned int GetId() const { return m_ID; }
	private:
		unsigned int m_ID;
	};
}

#define HC_COLOR_RED 1.0f, 0.0f, 0.0f, 1.0f
#define HC_COLOR_BLUE 0.0f, 0.0f, 1.0f, 1.0f
#define HC_COLOR_GREEN 0.0f, 1.0f, 0.0f, 1.0f
#define HC_COLOR_WHITE 1.0f, 1.0f, 1.0f, 1.0f
#define HC_COLOR_BLACK 0.0f, 0.0f, 0.0f, 1.0f