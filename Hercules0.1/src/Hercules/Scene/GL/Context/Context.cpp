#include "hcpch.h"

#include "Context.h"

#include <glfw/glfw3.h>
#include <glad/glad.h>

namespace Hercules {
	
	RenderingContext::RenderingContext(GLFWwindow* window)
		: m_Window(window)
	{
		HC_CORE_ASSERT(window, "Window is NULL");
	}
	void RenderingContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HC_CORE_ASSERT(status, "Could not initialize Glad");
	}
	void RenderingContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}