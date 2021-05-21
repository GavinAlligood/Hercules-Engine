#include "hcpch.h"

#include "Texture.h"

#include <glad/glad.h>
#include "Hercules/Renderer/stbi/stb_image.h"

Hercules::Texture::Texture(int sWrap, int tWrap, int minFilter, int magFilter,
	const char* filename, int format, int srcFormat, int dataFormat, int id)
	: m_ID(id)
{
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, srcFormat, dataFormat, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		HC_CORE_ERROR("Failed to load texture");
	}
	stbi_image_free(data);
}

Hercules::Texture::~Texture()
{
}

void Hercules::Texture::Bind() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}
