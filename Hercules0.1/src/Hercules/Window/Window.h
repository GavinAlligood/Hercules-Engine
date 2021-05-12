#pragma once

#include "Hercules/Application/Core.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Hercules {
	class HERCULES_API Window {
	public:
		Window(int height, int width);
		~Window();

		void winUpdate();

		inline GLFWwindow* GetWindow() { return m_Window; }
	private:
		GLFWwindow* m_Window;

		int m_Height, m_Width;
	};
}