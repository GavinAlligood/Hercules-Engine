#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Hercules/Scene/GL/Context/Context.h"

namespace Hercules {
	class Window {
	public:
		Window(int height, int width);
		~Window();

		void winUpdate();

		inline GLFWwindow* GetWindow() { return m_Window; }
	private:
		GLFWwindow* m_Window;

		int m_Height, m_Width;

		RenderingContext* m_Context;
	};
}