#pragma once

#include "Hercules/Core/Window/Window.h"

namespace Hercules {
	class Framebuffer {
	public:
		Framebuffer(int width, int height);
		~Framebuffer();

		void Create(int width, int height);
		void Destroy();

		void Bind() const;
		void Unbind() const;

		int ReadPixel(unsigned int index, int x, int y);

		const inline unsigned int GetID() const { return m_ID; }
		const inline unsigned int GetColorBuffer() const { return textureColorBuffer; }
	private:
		unsigned int m_ID;
		unsigned int m_DepthAttachment;
		unsigned int textureColorBuffer;
		unsigned int rbo;
	};
}