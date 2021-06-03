#pragma once

#include "hcpch.h"

namespace Hercules {

	enum class EventType
	{
		CursorMoved,
		KeyPressed,
		MousePressed
	};

	class Event {
	public:
		bool handled = false;

		virtual EventType GetType() const = 0;
	};

	class CursorMovedEvent : public Event {
	public:
		CursorMovedEvent(float xpos, float ypos)
			: m_Xpos(xpos), m_Ypos(ypos) {}

		inline float GetX() const { return m_Xpos; }
		inline float GetY() const { return m_Ypos; }
	protected:
		float m_Xpos, m_Ypos;

		EventType GetType() const override { return EventType::CursorMoved; }
	};

	class KeyPressedEvent : public Event {
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: m_Keycode(keycode), m_RepeatCount(repeatCount) {}

		inline int GetKeyCode() const { return m_Keycode; }
		inline int GetRepeatCount() const { return m_RepeatCount; }
	private:
		int m_Keycode, m_RepeatCount;
	};
}