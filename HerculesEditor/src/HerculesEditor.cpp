#include <../Hercules.h>

//TODO: FIX CRASHING ON MINIMIZE

using namespace Hercules;

class Editor : public Hercules::Application
{
public:
	Editor()
	{
		SpatialRenderer::Init();
		Camera::Init(5.0f);
	}

	~Editor()
	{
		//glDeleteFramebuffers(1, &framebuffer);
		SpatialRenderer::End();
		glfwTerminate();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void PlayerMovement()
	{
		if (InputManager::IsKeyPressed(HC_KEY_W))
		{
			Camera::MoveForward();
		}
		else if (InputManager::IsKeyPressed(HC_KEY_S))
		{
			Camera::MoveBackward();
		}
		if (InputManager::IsKeyPressed(HC_KEY_A))
		{
			Camera::MoveLeft();
		}
		else if (InputManager::IsKeyPressed(HC_KEY_D))
		{
			Camera::MoveRight();
		}
		if (InputManager::IsKeyPressed(HC_KEY_SPACE))
		{
			Camera::MoveUp();
		}
		else if (InputManager::IsKeyPressed(HC_KEY_LEFT_ALT))
		{
			Camera::MoveDown();
		}

		if (InputManager::IsMousePressed(HC_MOUSE_BUTTON_2))
		{
			holdingRight = true;
		}
		else
		{
			holdingRight = false;
		}
	}

	void Editor::Start() override
	{
		HC_INFO("Start");
		//					   component id        Entity ID
		SceneManager::AppendComponent(1, DemoComponent(1));
		SceneManager::AppendComponent(2, DemoComponent(2));
		SceneManager::AppendComponent(5, DemoComponent(5));
		SceneManager::AppendComponent(6, TransformComponent(1, glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f), dirt, glm::vec4(HC_COLOR_WHITE)));
		SceneManager::AppendComponent(7, TransformComponent(2, glm::vec3(-1.0f, 1.0f, 0.5f), glm::vec3(0.5f), glm::vec3(0.0f), dirt, glm::vec4(HC_COLOR_GREEN)));
		SceneManager::AppendComponent(8, TransformComponent(3, glm::vec3(2.0f, 0.5f, 0.0f), glm::vec3(1.0f), glm::vec3(25.0f, 45.0f, 0.0f), dirt, glm::vec4(HC_COLOR_WHITE)));
		SceneManager::AppendComponent(9, TransformComponent(5, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(45.0f, 0.0f, 0.0f), defaultTex, glm::vec4(HC_COLOR_WHITE)));
		SceneManager::AppendComponent(4, TransformComponent(6, glm::vec3(-1.2f, 1.0f, -6.0f), glm::vec3(1.0f), glm::vec3(0.0f), defaultTex, glm::vec4(HC_COLOR_WHITE)));
		SceneManager::AppendComponent(3, LightComponent(6, glm::vec3(1.0f, 1.0f, 1.0f))); //there always needs to be a little bit of a color for it to not appear black
	}

	void Editor::Update() override
	{
		Camera::UpdateTime();

		PlayerMovement();
	}

	void OnEvent(Event& e) override
	{
		//little glitchy but it works for now
		if (e.GetType() == EventType::CursorMoved && holdingRight)
		{
			CursorMovedEvent& c = (CursorMovedEvent&)e;
			Camera::Look(centerX + c.GetX(), centerY + c.GetY());
		}

		if (e.GetType() == EventType::WindowResize)
		{
			WindowResizeEvent& r = (WindowResizeEvent&)e;
			Camera::SetAspectRatio(r.GetWidth(), r.GetHeight());
			Camera::UpdateAspectRatio();
		}
	}

	void Editor::UpdateFramebuffer()
	{
		//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
		//glEnable(GL_DEPTH_TEST);


		//glClearColor(0.2f, 0.2f, 0.2f, 1);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Editor::ImGuiRender()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//ImGui::ShowDemoWindow();

		static bool p_open = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->GetWorkPos());
			ImGui::SetNextWindowSize(viewport->GetWorkSize());
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &p_open, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			
			if (ImGui::BeginMenu("Options"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows,
				// which we can't undo at the moment without finer window depth/z control.
				ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
				ImGui::MenuItem("Padding", NULL, &opt_padding);
				ImGui::Separator();

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::Separator();

				if (ImGui::MenuItem("Close", NULL, false))
					p_open = false;
					
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();

			////should definitely move this
			//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			//glDisable(GL_DEPTH_TEST);

			//glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			//glClear(GL_COLOR_BUFFER_BIT);

		}


		//Stats
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Performance");

			ImGui::Text("FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Text("Test Components: %.1i", SceneManager::GetDemoComponentList().size());
			ImGui::Text("Mesh Components: %.1i", SceneManager::GetMeshComponentList().size());
			ImGui::Text("Transform Components: %.1i", SceneManager::GetTransformComponentList().size());
			ImGui::Text("Light Components: %.1i", SceneManager::GetLightComponentList().size());
			ImGui::End();
		}

		{
			static float iVx;
			static float iVy;
			static float iVz;
			static float x = SceneManager::GetTransformComponent(6)->GetPos().x;
			static float y = SceneManager::GetTransformComponent(6)->GetPos().y;
			static float z = SceneManager::GetTransformComponent(6)->GetPos().z;

			ImGui::Begin("Editor");

			ImGui::DragFloat("X", &iVx, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::DragFloat("Y", &iVy, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::DragFloat("Z", &iVz, 0.1f, 0.0f, 0.0f, "%.2f");

			SceneManager::GetTransformComponent(6)->SetPos(glm::vec3(x + iVx, y + iVy, z + iVz));
			ImGui::End();
		}

		////'viewport'
		//{
		//	ImGui::Begin("Scene");
		//	//unsigned int frameTexture = framebuffer;
		//	//ImGui::Image((void*)framebuffer, ImVec2{ 320.0f, 180.0f });
		//	ImGui::End();
		//}

		ImGui::End();


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		//should definitely move this
		//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		//glDisable(GL_DEPTH_TEST);

		//glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT);

	}

	void Editor::ImGuiInit()
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImFont* consola = io.Fonts->AddFontFromFileTTF("Assets/Fonts/CONSOLA.TTF", 14.0f);
		//ImGui::PushFont(consola);

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		/*if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			
		}*/
		style.WindowRounding = 0.0f;
		/*style.Colors[ImGuiCol_WindowBg] = ImVec4(0.9f, 0.9f, 0.9f, 1.0f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);

		style.Colors[ImGuiCol_Text] = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);*/
		style.Colors[ImGuiCol_Text] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.62f, 0.62f, 0.62f, 1.00f);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_ChildBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_PopupBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_Border] = ImVec4(1.00f, 0.79f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.16f, 0.17f, 0.18f, 1.00f);
		style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.70f, 0.59f, 0.04f, 1.00f);
		style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.70f, 0.59f, 0.04f, 1.00f);
		style.Colors[ImGuiCol_TitleBg] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.70f, 0.59f, 0.04f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.70f, 0.59f, 0.04f, 1.00f);
		style.Colors[ImGuiCol_CheckMark] = ImVec4(0.90f, 0.90f, 0.90f, 0.50f);
		style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
		style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 0.79f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.70f, 0.59f, 0.04f, 1.00f); 
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.70f, 0.59f, 0.04f, 1.00f);
		style.Colors[ImGuiCol_Header] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.70f, 0.59f, 0.04f, 1.00f);
		style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.70f, 0.59f, 0.04f, 1.00f);
		style.Colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(1.00f, 0.79f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_SeparatorActive] = ImVec4(1.00f, 0.79f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 0.69f, 0.07f, 0.14f);
		style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 0.79f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 0.79f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_TabHovered] = ImVec4(0.70f, 0.59f, 0.04f, 1.00f);
		style.Colors[ImGuiCol_TabActive] = ImVec4(0.70f, 0.59f, 0.04f, 1.00f);
		style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.79f, 0.79f, 0.79f, 1.00f);
		style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
		style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.70f, 0.59f, 0.04f, 1.00f);
		style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.75f, 0.30f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.75f, 0.30f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		style.Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		style.Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);

		ImGui_ImplGlfw_InitForOpenGL(Application::Get().GetWindow().GetWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

private:
	Texture defaultTex = Texture("Assets/Textures/default_texture.jpg", 0, HC_IMG_JPG);
	Texture skeleton = Texture("Assets/Textures/drawnSkeleton.png", 0, HC_IMG_PNG);
	Texture dirt = Texture("Assets/Textures/dirtMinecraft.jpg", 0, HC_IMG_JPG);

	bool polygon = false;
	bool point = false;
	bool holdingRight = false;
	float centerX = 480, centerY = 270;

	//imgui testing
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	//Framebuffer
	//unsigned int framebuffer = 0;
};

Hercules::Application* Hercules::CreateApplication()
{
	return new Editor();
}