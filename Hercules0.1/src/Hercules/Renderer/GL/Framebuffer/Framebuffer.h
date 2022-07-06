#pragma once

#include "Hercules/Core/Window/Window.h"

namespace Hercules {
	class Framebuffer {
	public:
		Framebuffer(int width, int height) {};
		~Framebuffer() {};

		static void Create(int width, int height);
		static void Destroy();

		static void Bind();
		static void Unbind();

		static int ReadPixel(unsigned int index, int x, int y);

		static const unsigned int GetID();
		static const unsigned int GetColorBuffer();
		static const unsigned int GetIntBuffer();
	};

	struct FramebufferData {
		unsigned int m_ID;
		unsigned int m_DepthAttachment;
		unsigned int m_ColorBuffer;
		unsigned int m_IntBuffer;
	};
}