#include "hcpch.h"

#include "Hercules/Input/Input.h"

#include "Hercules/Application/Application.h"

//Todo: Add some sort of callback system

namespace Hercules {
	bool InputManager::IsKeyPressed(int keycode)
	{
		auto window = Application::Get().GetWindow().GetWindow();
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS;
	}

	bool InputManager::IsMousePressed(int btn)
	{
		auto window = Application::Get().GetWindow().GetWindow();
		auto state = glfwGetMouseButton(window, btn);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> InputManager::GetMousePos()
	{
		double x, y;
		auto window = Application::Get().GetWindow().GetWindow();
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, (float)y };
	}
}