#pragma once

#include "Core.h"

#include "Hercules/Window/Window.h"

#include "Hercules/Renderer/Vertex/VertexBuffer.h"
#include "Hercules/Renderer/Shader/Shader.h"

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

		void checkClose();

		inline static Application& Get() { return *s_Instace; }
		inline Window& GetWindow() { return *window; }
	private:
		bool m_Running = true;
		static Application* s_Instace;
		Window* window = nullptr;

		Shader* shader = nullptr;
		unsigned int m_VertexArray, m_IndexBuffer;

		std::string vertexPath, fragmentPath;
	};

	//Will be defined in client
	Application* CreateApplication();
}
