#include "hcpch.h"

#include "Texture.h"

#include <glad/glad.h>
#include "../vendor/stbi/stb_image.h"

Hercules::Texture::Texture(const char* filename, int id, bool type)
	: m_ID(id)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//SceneManager::GetTextureList().size()
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, channels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

	if (data)
	{
		if (type)
		{
			//need to change
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}
	else
	{
		HC_CORE_ERROR("Failed to load texture: {0}", filename);
	}
	
	stbi_image_free(data);
}

void Hercules::Texture::Bind() const
{
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}
