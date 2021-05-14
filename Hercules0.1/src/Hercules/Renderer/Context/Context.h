#pragma once

struct GLFWwindow;

namespace Hercules {
	class RenderingContext
	{
	public:
		RenderingContext(GLFWwindow* window);

		virtual void Init();
		virtual void SwapBuffers();
	private:
		GLFWwindow* m_Window;
	};
}