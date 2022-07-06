#include "hcpch.h"

#include "Framebuffer.h"

#include <glad/glad.h>

namespace Hercules {
	
	FramebufferData EditorFramebufferData;

	void Hercules::Framebuffer::Create(int width, int height)
	{
		if (EditorFramebufferData.m_ID)
		{
			glDeleteFramebuffers(1, &EditorFramebufferData.m_ID);
			glDeleteTextures(1, &EditorFramebufferData.m_ColorBuffer);
			glDeleteTextures(1, &EditorFramebufferData.m_IntBuffer);
			glDeleteTextures(1, &EditorFramebufferData.m_DepthAttachment);
		}

		glGenFramebuffers(1, &EditorFramebufferData.m_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, EditorFramebufferData.m_ID);

		//Color attachment
		glGenTextures(1, &EditorFramebufferData.m_ColorBuffer);
		glBindTexture(GL_TEXTURE_2D, EditorFramebufferData.m_ColorBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, EditorFramebufferData.m_ColorBuffer, 0);

		//Int Attachment
		glGenTextures(1, &EditorFramebufferData.m_IntBuffer);
		glBindTexture(GL_TEXTURE_2D, EditorFramebufferData.m_IntBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, width, height, 0, GL_RED_INTEGER, GL_INT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, EditorFramebufferData.m_IntBuffer, 0);

		//Depth and stencil attachment
		glGenTextures(1, &EditorFramebufferData.m_DepthAttachment);
		glBindTexture(GL_TEXTURE_2D, EditorFramebufferData.m_DepthAttachment);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL,
			GL_UNSIGNED_INT_24_8, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, EditorFramebufferData.m_DepthAttachment, 0);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			HC_CORE_FATAL("ERROR! Framebuffer is not complete!");

		GLenum buffers[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };

		glDrawBuffers(2, buffers);
		//glEnable(GL_DEPTH_TEST);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Hercules::Framebuffer::Destroy()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteFramebuffers(1, &EditorFramebufferData.m_ID);
		glDeleteTextures(1, &EditorFramebufferData.m_ColorBuffer);
		glDeleteTextures(1, &EditorFramebufferData.m_IntBuffer);
		glDeleteTextures(1, &EditorFramebufferData.m_DepthAttachment);
	}

	void Hercules::Framebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, EditorFramebufferData.m_ID);
	}

	void Hercules::Framebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	int Hercules::Framebuffer::ReadPixel(unsigned int index, int x, int y)
	{
		//Bind();
		glDisable(GL_DEPTH_TEST);
		glReadBuffer(GL_COLOR_ATTACHMENT0 + index); // + index
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData); // GL_RGBA
		return pixelData;
	}
	const unsigned int Framebuffer::GetID()
	{
		return EditorFramebufferData.m_ID;
	}
	const unsigned int Framebuffer::GetColorBuffer()
	{
		return EditorFramebufferData.m_ColorBuffer;
	}
	const unsigned int Framebuffer::GetIntBuffer()
	{
		return EditorFramebufferData.m_IntBuffer;
	}
}