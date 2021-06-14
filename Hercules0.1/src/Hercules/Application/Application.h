#pragma once

#include "Core.h"

#include "Hercules/Core/Window/Window.h"

//OpenGL
#include "Hercules/Renderer/GL/Index/IndexBuffer.h"
#include "Hercules/Renderer/GL/Vertex/VertexBuffer.h"
#include "Hercules/Renderer/GL/Shader/Shader.h"

#include "Hercules/Core/Events.h"

//Rendering
#include "Hercules/Scene/SceneManager.h"
#include "Hercules/Scene/Camera/Camera.h"
#include "Hercules/Renderer/3D/3DRenderer.h"
#include "Hercules/Renderer/2D/2DRenderer.h"

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
		void Render();
		void UpdateLight();

		void checkClose();
		void CalculateFrameRate();

		inline static Application& Get() { return *s_Instace; }
		inline Window& GetWindow() { return *window; }
	private:
		bool m_Running = true;
		static Application* s_Instace;
		Window* window = nullptr;

		bool InScene = true;

		Shader* shader = nullptr;
	};

	//Will be defined in client
	Application* CreateApplication();
}