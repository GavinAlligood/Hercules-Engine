#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Hercules/Renderer/GL/Context/Context.h"

#include "Hercules/Core/Events.h"

namespace Hercules {
	class Window {
	public:
		Window(int height, int width);
		~Window();

		void winUpdate();

		inline GLFWwindow* GetWindow() { return m_Window; }

		typedef std::function<void(Event&)> EventCallback;
		EventCallback eventCallback;

		inline void SetEventCallback(const EventCallback& callback) { eventCallback = callback; }
	private:
		GLFWwindow* m_Window;

		int m_Height, m_Width;

		RenderingContext* m_Context;
	};
}