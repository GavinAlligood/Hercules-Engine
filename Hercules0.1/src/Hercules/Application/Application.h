#pragma once
//i need to organize the functions here better

#include "Hercules/Core/Core.h"

#include "Hercules/Core/Window/Window.h"

//OpenGL
#include "Hercules/Renderer/GL/Index/IndexBuffer.h"
#include "Hercules/Renderer/GL/Vertex/VertexBuffer.h"
#include "Hercules/Renderer/GL/Shader/Shader.h"
#include "Hercules/Renderer/GL/Framebuffer/Framebuffer.h"

#include "Hercules/Core/Events.h"

//Rendering
#include "Hercules/Scene/Camera/Camera.h"
#include "Hercules/Renderer/3D/3DRenderer.h"
//#include "Hercules/Renderer/2D/2DRenderer.h"

//ECS
#include "Hercules/Scene/SceneManager.h"

#include "imgui/imgui.h"
#include "imgui/examples/imgui_impl_glfw.h"
#include "imgui/examples/imgui_impl_opengl3.h"

#include "Hercules/Renderer/Model/Model.h"

namespace Hercules {

	class Application
	{
	public:
		Application(const char* name, std::string projectPath);
		virtual ~Application();

		void Run();

		virtual void Start() = 0;
		virtual void Update() = 0;
		void OnApplicationEvent(Event& e);
		virtual void OnEvent(Event& e) {};
		void Render();
		void UpdateLight();
		virtual void ImGuiRender() {};
		virtual void ImGuiInit() {};
		virtual void UpdateFramebuffer() {};

		void Close();

		void checkClose();
		bool OnWindowResize(WindowResizeEvent& e);

		inline static Application& Get() { return *s_Instace; }
		inline Window& GetWindow() { return *window; }
	private:
		bool m_Running = true;
		bool m_Minimized = false;
		static Application* s_Instace;
		Window* window = nullptr;

		bool InScene = true;

		Shader* shader = nullptr;

		Model* model = nullptr;
	};

	//Will be defined in client
	Application* CreateApplication();
}