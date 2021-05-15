#include "hcpch.h"

#include "Shader.h"

#include <glad/glad.h>

Hercules::Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
	std::ifstream vertexFile;
	vertexFile.open(vertexPath);
	std::stringstream vertexSrc;
	vertexSrc << vertexFile.rdbuf();
	vertexFile.close();
	std::string vertexStr = vertexSrc.str();

	std::ifstream fragmentFile;
	fragmentFile.open(fragmentPath);
	std::stringstream fragmentSrc;
	fragmentSrc << fragmentFile.rdbuf();
	fragmentFile.close();
	std::string fragmentStr = fragmentSrc.str();

	const char* vShaderSrc = vertexStr.c_str();
	const char* fShaderSrc = fragmentStr.c_str();

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
}

Hercules::Shader::~Shader()
{
	glDeleteProgram(m_ID);
}

void Hercules::Shader::Bind() const
{
	glUseProgram(m_ID);
}
