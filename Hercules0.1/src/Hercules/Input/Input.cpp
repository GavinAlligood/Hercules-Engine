#include "hcpch.h"

#include "Hercules/Input/Input.h"

#include "Hercules/Application/Application.h"

namespace Hercules {
	bool InputManager::IsKeyPressed(int keycode)
	{
		//get window
		auto window = Application::Get().GetWindow().GetWindow();
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS;
	}
}