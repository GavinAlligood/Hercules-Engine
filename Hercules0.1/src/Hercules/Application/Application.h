#pragma once

#include "Core.h"

#include "Hercules/Window/Window.h"

namespace Hercules {

	class HERCULES_API Application
	{
	public:
		Application();
		//will be inherited from
		virtual ~Application();

		void Run();

		virtual void Start() = 0;
		virtual void Update() = 0;

		inline static Application& Get() { return *s_Instace; }
		inline Window& GetWindow() { return *window; }
	private:
		bool m_Running = true;
		static Application* s_Instace;
		Window* window = nullptr;
	};

	//Will be defined in client
	Application* CreateApplication();
}
