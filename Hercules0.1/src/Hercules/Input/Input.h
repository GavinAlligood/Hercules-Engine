#pragma once

#include "Hercules/Application/Core.h"
#include <GLFW/glfw3.h>

#include "Keycodes.h"
#include "MouseCodes.h"

namespace Hercules {
	class HERCULES_API InputManager {
	public:
		InputManager() {};

		static bool IsKeyPressed(int keycode);
		static bool IsMousePressed(int btn);

		static std::pair<float, float> GetMousePos();
	private:
		//static GLFWwindow* s_Window;
		static InputManager* s_Instace;
	};
}