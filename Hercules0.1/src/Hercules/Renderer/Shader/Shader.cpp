#include "hcpch.h"

#include "Shader.h"

#include <glad/glad.h>

Hercules::Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
{
	const char* vShaderSrc = vertexSrc.c_str();
	const char* fShaderSrc = fragmentSrc.c_str();

	int success;
	char infoLog[512];

	//Vertex shader
	GLint vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderSrc, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		HC_CORE_ERROR("Failed to compile Vertex Shader!");
		HC_CORE_ERROR(infoLog);
	}

	//Fragment shader
	GLint fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderSrc, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		HC_CORE_ERROR("Failed to compile Fragment Shader!");
		HC_CORE_ERROR(infoLog);
	}

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertex);
	glAttachShader(m_ID, fragment);
	glLinkProgram(m_ID);
	glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
		HC_CORE_ERROR("Failed to link shader!");
		HC_CORE_ERROR(infoLog);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Hercules::Shader::~Shader()
{
	glDeleteProgram(m_ID);
}

void Hercules::Shader::Bind() const
{
	glUseProgram(m_ID);
}
