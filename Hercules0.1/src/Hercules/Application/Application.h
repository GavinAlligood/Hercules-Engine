#pragma once

#include "Core.h"

#include "Hercules/Core/Window/Window.h"

#include "Hercules/Renderer/GL/Index/IndexBuffer.h"
#include "Hercules/Renderer/GL/Vertex/VertexBuffer.h"
#include "Hercules/Renderer/GL/Shader/Shader.h"

#include "Hercules/Core/Events.h"

namespace Hercules {

	class Application
	{
	public:
		Application();
		//will be inherited from
		virtual ~Application();

		void Run();

		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void OnEvent(Event& e) = 0;

		void checkClose();

		inline static Application& Get() { return *s_Instace; }
		inline Window& GetWindow() { return *window; }
	private:
		bool m_Running = true;
		static Application* s_Instace;
		Window* window = nullptr;

		bool InScene = true;
	};

	//Will be defined in client
	Application* CreateApplication();
}