#pragma once

namespace Hercules {
	class SettingsMenu {
	public:
		SettingsMenu() {};
		~SettingsMenu() {};

		static void ConditionalRender();

		static void UseStyleDarkMode();
		static void UseStyleLightMode();
	};
}