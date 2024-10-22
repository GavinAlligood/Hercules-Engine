#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Hercules/Renderer/GL/Context/Context.h"

#include "Hercules/Core/Events.h"

namespace Hercules {
	class Window {
	public:
		Window(const char* name, int height, int width);
		~Window();

		void winUpdate();

		inline GLFWwindow* GetWindow() { return m_Window; }

		inline int GetHeight() const { return m_Height; }
		inline int GetWidth() const { return m_Width; }

		typedef std::function<void(Event&)> EventCallback;
		EventCallback eventCallback;

		inline void SetEventCallback(const EventCallback& callback) { eventCallback = callback; }
	private:
		GLFWwindow* m_Window;

		int m_Height, m_Width;

		RenderingContext* m_Context;
	};
}