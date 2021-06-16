#include "hcpch.h"
#include "Application.h"

#include "Hercules/Core/Log/Log.h"
#include "Hercules/Core/Input/Input.h"

#include <glad/glad.h>

//Note:
//If any game is going to have some sort of typing, i will probably need a glfwKeyCallback function
//I should also add a way to not need glm::vec3 every time i use a vector

//So i still need to work on the 2D renderer but im going to focus on
//3d more since thats the kind of games I want to make in this engine

namespace Hercules {

#define HC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

	Application* Application::s_Instace = nullptr;

	Hercules::Application::Application()
	{
		s_Instace = this;

		window = new Window(540, 960);

		shader = new Shader("Assets/Shaders/Vertex.shader",
			"Assets/Shaders/Fragment.shader");

		window->SetEventCallback(HC_BIND_EVENT_FN(Application::OnEvent));
	}

	Hercules::Application::~Application()
	{
		delete window;
		delete shader;
		/*glfwTerminate();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();*/
	}

	void Application::Run()
	{
		Start();

		//in scene by default
		//glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");

		while (m_Running)
		{
			checkClose();
			//CalculateFrameRate();

			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			/*ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();*/
			

			UpdateLight();

			glActiveTexture(GL_TEXTURE0);

			Update();
			Render();
		

			//ImGui::ShowDemoWindow();

			////Performance
			//{
			//	static float f = 0.0f;
			//	static int counter = 0;

			//	ImGui::Begin("Performance");

			//	ImGui::Text("FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			//	ImGui::End();
			//}

			//{
			//	static float iVx;
			//	static float iVy;
			//	static float iVz;
			//	static float x = SceneManager::GetTransformComponent(6)->GetPos().x;
			//	static float y = SceneManager::GetTransformComponent(6)->GetPos().y;
			//	static float z = SceneManager::GetTransformComponent(6)->GetPos().z;

			//	ImGui::Begin("Editor");

			//	ImGui::DragFloat("X", &iVx, 0.1f, 0.0f, 0.0f, "%.2f");
			//	ImGui::DragFloat("Y", &iVy, 0.1f, 0.0f, 0.0f, "%.2f");
			//	ImGui::DragFloat("Z", &iVz, 0.1f, 0.0f, 0.0f, "%.2f");

			//	SceneManager::GetTransformComponent(6)->SetPos(glm::vec3(x + iVx, y + iVy, z + iVz));
			//	ImGui::End();
			//}

			//ImGui::Render();
			//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			ImGuiRender();

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}

			window->winUpdate();
		}
	}

	void Application::Render()
	{
		if (SceneManager::GetTransformComponentList().size() != 0)
		{
			std::map<unsigned int, TransformComponent>::iterator it;
			for (it = SceneManager::GetTransformComponentList().begin();
				it != SceneManager::GetTransformComponentList().end(); ++it)
			{
				//0.2f 1.0f 0.3f
				shader->SetVec3("objectColor", (*it).second.GetColor());
				SpatialRenderer::DrawCube((*it).second.GetTexture(),
					glm::vec3((*it).second.GetPos()),
					glm::vec3((*it).second.GetScale()),
					glm::vec3((*it).second.GetRotation()),
					glm::vec4((*it).second.GetColor()),
					SCENE_CAMERA, shader);

				if (SceneManager::HasLightComponent((*it).second.GetId()))
				{
					shader->SetVec3("lightPos", (*it).second.GetPos());
				}
			}
		}
	}

	void Application::UpdateLight()
	{
		shader->SetVec3("viewPos", Camera::GetPos());
		std::map<unsigned int, LightComponent>::iterator li;
		for (li = SceneManager::GetLightComponentList().begin();
			li != SceneManager::GetLightComponentList().end(); ++li)
		{
			//this is definately not going to work when i have multiple lights
			shader->SetVec3("lightColor", (*li).second.GetColor());
		}
	}

	void Application::checkClose()
	{
		if (glfwWindowShouldClose(window->GetWindow()))
		{
			m_Running = false;
		}
	}

	//Make a macro to control this
	void Application::CalculateFrameRate()
	{
		static float framesPerSecond = 0.0f;
		static float lastTime = 0.0f;
		float currentTime = GetTickCount64() * 0.001f;
		++framesPerSecond;
		if (currentTime - lastTime > 1.0f)
		{
			lastTime = currentTime;
			HC_CORE_INFO("Current Frames Per Second: {0}", (int)framesPerSecond);
			framesPerSecond = 0;
		}
	}
}