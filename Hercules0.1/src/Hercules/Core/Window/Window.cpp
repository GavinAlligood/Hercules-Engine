#include "hcpch.h"

#include "Window.h"

namespace Hercules {
	Window::Window(const char* name, int height, int width)
		: m_Height(height), m_Width(width)
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//dont hardcode size
		m_Window = glfwCreateWindow(m_Width, m_Height, name, NULL, NULL);
		
		if (m_Window == NULL)
		{
			glfwTerminate;
			HC_FATAL("Could not create window!");
		}

		m_Context = new RenderingContext(m_Window);
		m_Context->Init();
		
		glfwSetWindowUserPointer(m_Window, this);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
				Window& win = *(Window*)glfwGetWindowUserPointer(window);

				win.m_Width = width;
				win.m_Height = height;
				
				WindowResizeEvent event(width, height);
				win.eventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
				Window& win = *(Window*)glfwGetWindowUserPointer(window);

				CursorMovedEvent event(xpos, ypos);
				win.eventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
				Window& win = *(Window*)glfwGetWindowUserPointer(window);
				KeyPressedEvent event(key);
				win.eventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
				Window& win = *(Window*)glfwGetWindowUserPointer(window);

				MousePressedEvent event(button);
				win.eventCallback(event);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double x, double y)
		{
				Window& win = *(Window*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event(x,y);
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
}