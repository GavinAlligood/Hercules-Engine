#pragma once

#include "Hercules/Core/Core.h"

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

#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_glfw.h"
#include "imgui/examples/imgui_impl_opengl3.h"

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


		//imgui testing
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	};

	//Will be defined in client
	Application* CreateApplication();
}