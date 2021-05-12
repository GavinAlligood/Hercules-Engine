#include "hcpch.h"

#include "Shader.h"

#include "glad/glad.h"

Hercules::Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexShader;
	std::string fragmentShader;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		vShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexShader = vShaderStream.str();
		fragmentShader = fShaderStream.str();
	}
	catch(std::ifstream::failure e)
	{
		HC_ERROR("Failed to read shader file!");
	}

	const char* vShaderCode = vertexShader.c_str();
	const char* fShaderCode = fragmentShader.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	//Vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		HC_ERROR("Could not compile vertex shader!");
		HC_ERROR(infoLog);
	}

	//Fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		HC_ERROR("Could not compile fragment shader!");
		HC_ERROR(infoLog);
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		HC_ERROR("Could not link shader!");
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Hercules::Shader::Use() const
{
	glUseProgram(ID);
}