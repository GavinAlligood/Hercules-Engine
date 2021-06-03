#include "hcpch.h"

#include "Window.h"

namespace Hercules {
	Window::Window(int height, int width)
		: m_Height(height), m_Width(width)
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
		
		glfwSetWindowUserPointer(m_Window, this);

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int w, int h)
		{
				glViewport(0, 0, w, h);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
				Window& win = *(Window*)glfwGetWindowUserPointer(window);

				CursorPos event(xpos, ypos);
				win.eventCallback(event);
		});
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

	bool Window::CursorPosCallback(float xpos, float ypos)
	{


		return true;
	}
}