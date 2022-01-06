#include <../Hercules.h>

#include "imgui_internal.h"
#include "../../HerculesEditor/src/HerculesEditor.h"

#define IMGUI_DEFINE_MATH_OPERATORS

namespace Hercules {

	class ProjectHub : public Hercules::Application
	{
	public:
		ProjectHub(const char* name, std::string projectPath, bool isGame)
			: Application(name, projectPath, isGame)
		{
		}

		~ProjectHub()
		{
			glfwTerminate();
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}

		//need work
		

		void ProjectHub::Start() override {}

		void ProjectHub::Update() override
		{
			//1. Get saved list of projects (a file) (there should be a set project directory path)
			//2. When selecting a project, start a new editor with that project.
		}

		void OnEvent(Event& e) override {}

		void ProjectHub::ImGuiRender()
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::ShowDemoWindow();

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

			if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
				window_flags |= ImGuiWindowFlags_NoBackground;

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

			//Menu bar
			if (ImGui::BeginMenuBar())
			{
				if (ImGui::BeginMenu("Project"))
				{
					if (ImGui::MenuItem("Open Project"))
					{
						//Open Hercules project hub
						ImGui::Text("Test");
						
					}
				}

				ImGui::EndMenuBar();
			}

			if (ImGui::Begin("Project Hub"))
			{
				if (ImGui::Button("Demo Project"))
				{
					//new editor
				}
				ImGui::End();
			}

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
		}

		void ProjectHub::ImGuiInit()
		{
			HC_CORE_TRACE("Initializing...");
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
			io.ConfigFlags |= ImGuiWindowFlags_Popup;

			//TODO: make a font size editor
			ImFont* consola = io.Fonts->AddFontFromFileTTF("Resources/Fonts/CONSOLA.TTF", 14.0f);

			ImGuiStyle& style = ImGui::GetStyle();
			style.WindowRounding = 8.0f;

			//TODO: Change when upgrading opengl
			ImGui_ImplGlfw_InitForOpenGL(Application::Get().GetWindow().GetWindow(), true);
			ImGui_ImplOpenGL3_Init("#version 330");
		}

		void ProjectHub::UseStyleLightMode()
		{
			ImVec4* colors = ImGui::GetStyle().Colors;

			colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
			colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
			colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
			colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_FrameBg] = ImVec4(0.838f, 0.838f, 0.838f, 1.000f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
			colors[ImGuiCol_TitleBg] = ImVec4(0.791f, 0.791f, 0.791f, 1.000f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
			colors[ImGuiCol_MenuBarBg] = ImVec4(0.597f, 0.597f, 0.597f, 1.000f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
			colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 0.877f, 0.557f, 1.000f);
			colors[ImGuiCol_SliderGrab] = ImVec4(1.000f, 0.933f, 0.557f, 1.000f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.863f, 0.557f, 1.000f);
			colors[ImGuiCol_Button] = ImVec4(0.717f, 0.717f, 0.717f, 0.400f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.859f, 0.835f, 0.472f, 1.000f);
			colors[ImGuiCol_Header] = ImVec4(0.718f, 0.718f, 0.718f, 0.400f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
			colors[ImGuiCol_HeaderActive] = ImVec4(0.853f, 0.829f, 0.465f, 1.000f);
			colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
			colors[ImGuiCol_SeparatorHovered] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(0.864f, 0.840f, 0.479f, 1.000f);
			colors[ImGuiCol_Tab] = ImVec4(0.718f, 0.718f, 0.718f, 0.400f);
			colors[ImGuiCol_TabHovered] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
			colors[ImGuiCol_TabActive] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
			colors[ImGuiCol_TabUnfocused] = ImVec4(0.792f, 0.792f, 0.792f, 1.000f);
			colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.941f, 0.941f, 0.941f, 1.000f);
			colors[ImGuiCol_DockingPreview] = ImVec4(1.000f, 0.973f, 0.557f, 0.780f);
			colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.775f, 0.775f, 0.775f, 1.000f);
			colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
			colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
			colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
			colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
			colors[ImGuiCol_NavHighlight] = colors[ImGuiCol_HeaderHovered];
			colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
			colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
			colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
		}

		void ProjectHub::UseStyleDarkMode()
		{
			ImVec4* colors = ImGui::GetStyle().Colors;

			colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
			colors[ImGuiCol_WindowBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
			colors[ImGuiCol_ChildBg] = ImVec4(0.32f, 0.32f, 0.32f, 0.00f);
			colors[ImGuiCol_PopupBg] = ImVec4(0.16f, 0.16f, 0.16f, 0.94f);
			colors[ImGuiCol_Border] = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
			colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
			colors[ImGuiCol_FrameBg] = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
			colors[ImGuiCol_FrameBgHovered] = ImVec4(0.98f, 0.98f, 0.98f, 0.40f);
			colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
			colors[ImGuiCol_TitleBg] = ImVec4(0.23f, 0.23f, 0.23f, 1.00f);
			colors[ImGuiCol_TitleBgActive] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
			colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
			colors[ImGuiCol_MenuBarBg] = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
			colors[ImGuiCol_ScrollbarBg] = ImVec4(0.11f, 0.11f, 0.11f, 0.71f);
			colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
			colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
			colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			colors[ImGuiCol_SliderGrab] = ImVec4(0.81f, 0.81f, 0.81f, 1.00f);
			colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			colors[ImGuiCol_Button] = ImVec4(0.46f, 0.46f, 0.46f, 0.40f);
			colors[ImGuiCol_ButtonHovered] = ImVec4(0.72f, 0.72f, 0.72f, 1.00f);
			colors[ImGuiCol_ButtonActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
			colors[ImGuiCol_Header] = ImVec4(0.45f, 0.45f, 0.45f, 0.40f);
			colors[ImGuiCol_HeaderHovered] = ImVec4(0.72f, 0.72f, 0.72f, 1.00f);
			colors[ImGuiCol_HeaderActive] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
			colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.40f, 0.50f);
			colors[ImGuiCol_SeparatorHovered] = ImVec4(0.73f, 0.73f, 0.73f, 0.78f);
			colors[ImGuiCol_SeparatorActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
			colors[ImGuiCol_ResizeGrip] = ImVec4(0.62f, 0.62f, 0.62f, 0.25f);
			colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.82f, 0.82f, 0.82f, 0.67f);
			colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.95f);
			colors[ImGuiCol_Tab] = ImVec4(0.30f, 0.30f, 0.30f, 0.86f);
			colors[ImGuiCol_TabHovered] = ImVec4(0.72f, 0.72f, 0.72f, 1.00f);
			colors[ImGuiCol_TabActive] = ImVec4(0.58f, 0.58f, 0.58f, 1.00f);
			colors[ImGuiCol_TabUnfocused] = ImVec4(0.24f, 0.24f, 0.24f, 0.97f);
			colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
			colors[ImGuiCol_DockingPreview] = ImVec4(0.88f, 0.88f, 0.88f, 0.70f);
			colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
			colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
			colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
			colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
			colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
			colors[ImGuiCol_TextSelectedBg] = ImVec4(0.93f, 0.93f, 0.93f, 0.35f);
			colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
			colors[ImGuiCol_NavHighlight] = ImVec4(0.93f, 0.93f, 0.93f, 1.00f);
			colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
			colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
			colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);


		}

	private:
		//imgui testing
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	};

	Hercules::Application* Hercules::CreateApplication()
	{
		return new ProjectHub("HerculesProjectHub", "null", false);
	}
}