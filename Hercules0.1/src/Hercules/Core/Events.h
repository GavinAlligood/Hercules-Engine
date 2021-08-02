#pragma once

#include "hcpch.h"

namespace Hercules {

	enum class EventType
	{
		CursorMoved,
		KeyPressed,
		MousePressed, MouseScrolled,
		WindowResize
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

		inline void SetX(float x) { m_Xpos = x; }
		inline void SetY(float y) { m_Ypos = y; }
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

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(double x, double y)
			: m_X(x), m_Y(y) {};
		~MouseScrolledEvent() {};

		inline double GetX() const { return m_X; }
		inline double GetY() const { return m_Y; }

	protected:
		double m_X;
		double m_Y;

		EventType GetType() const override { return EventType::MouseScrolled; }
	};

	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height) {};

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		static EventType GetStaticType() { return EventType::WindowResize; }
		EventType GetType() const override { return GetStaticType(); }
	protected:
		int m_Width, m_Height;
	};

	class EventDispatcher
	{
		//function pointer
		template<typename T>
		using EventFn = std::function<bool(T&)>; //i forgot a semicolon here and was wondering why i got 255 errors
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetType() == T::GetStaticType())
			{
				m_Event.handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
}