#pragma once

namespace Hercules {
	class CursorPos {
	public:
		CursorPos(float xpos, float ypos)
			: m_Xpos(xpos), m_Ypos(ypos) {}

		inline float GetX() const { return m_Xpos; }
		inline float GetY() const { return m_Ypos; }
	private:
		float m_Xpos, m_Ypos;

		bool handled = false;
	};
}