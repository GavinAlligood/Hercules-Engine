#pragma once

#include "Hercules/Core/Core.h"
#include <GLFW/glfw3.h>

#include "Keycodes.h"
#include "MouseCodes.h"

namespace Hercules {
	class InputManager {
	public:
		InputManager() {};

		static bool IsKeyPressed(int keycode);
		static bool IsMousePressed(int btn);

		static std::pair<float, float> GetMousePos();

		static float GetMouseX();
		static float GetMouseY();
	};
}