#pragma once

namespace Hercules {
	class QuickMenu {
	public:
		QuickMenu(bool check);
		~QuickMenu();

		static void ConditionalRender();
	private:
		bool m_DisplayCheck;
	};
}