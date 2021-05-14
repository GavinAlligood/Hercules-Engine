#include "hcpch.h"

#include "Window.h"

#include "Hercules/Renderer/Context.h"

namespace Hercules {
	Window::Window(int height, int width)
		: m_Width(width), m_Height(height)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//dont hardcode size
		m_Window = glfwCreateWindow(m_Width, m_Height, "Hercules", NULL, NULL);

		if (m_Window == NULL)
		{
			glfwTerminate;
			HC_FATAL("Could not create window!");
		}

		m_Context = new RenderingContext(m_Window);
		m_Context->Init();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
	}

	void Window::winUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	/*void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}*/
}