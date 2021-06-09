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
		KeyPressedEvent(int keycode)
			: m_Keycode(keycode) {}

		inline int GetKeyCode() const { return m_Keycode; }
	protected:
		int m_Keycode;

		EventType GetType() const override { return EventType::KeyPressed; }
	};

	class MousePressedEvent : public Event {
	public:
		MousePressedEvent(int button) 
		: m_Button(button) {};

		inline int GetMouseButton() const { return m_Button; }
	protected:
		int m_Button;

		EventType GetType() const override { return EventType::MousePressed; }
	};
}