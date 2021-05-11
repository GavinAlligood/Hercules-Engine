#pragma once

#include "Hercules/Application/Core.h"
#include <GLFW/glfw3.h>

#include "Keycodes.h"

//TODO: Make some kind of way to get window

namespace Hercules {
	class HERCULES_API InputManager {
	public:
		InputManager() {};

		static bool IsKeyPressed(int keycode);
	private:
		//static GLFWwindow* s_Window;
		static InputManager* s_Instace;
	};
}