#include "UIRenderer.h"

//TODO: Potentially move framebuffer into UIData instead

namespace Hercules {
	
	UIData EditorUIData;

	UIRenderer::UIRenderer() {}

	UIRenderer::~UIRenderer() {}

	void UIRenderer::Init()
	{
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

	void UIRenderer::NewFrame()
	{
		//m_Framebuffer.Unbind();
		Framebuffer::Unbind();
		//EditorUIData.m_Framebuffer.Unbind();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void UIRenderer::Render()
	{
		NewFrame();

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

		//Quick Menu
		QuickMenu::ConditionalRender();
		//Menu Bar
		MenuBar::ConditionalRender();
		//Settings Menu
		SettingsMenu::ConditionalRender();
		//Stats Menu
		StatsMenu::ConditionalRender();
		//Component View
		ComponentView::ConditionalRender();
		//Toolbar
		//Toolbar::ConditionalRender();
		//Viewport
		Viewport::ConditionalRender();
		//Scene Hierarchy
		SceneHeirarchy::ConditionalRender();

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

	void UIRenderer::SetLevels(std::string projectPath, std::string editorLevel, std::string runtimeLevel, std::string currentLevel)
	{
		EditorUIData.ProjectPath = projectPath;
		EditorUIData.EditorLevel = editorLevel;
		EditorUIData.RuntimeLevel = runtimeLevel;
		EditorUIData.CurrentLevel = currentLevel;
	}

	void UIRenderer::CreateIcons()
	{
		/*Texture FolderIcon = Texture("Resources/Icons/folder.png", 1, true);
		Texture FileIcon = Texture("Resources/Icons/document.png", 1, true);
		Texture ImageIcon = Texture("Resources/Icons/picture.png", 1, true);
		Texture FontIcon = Texture("Resources/Icons/font.png", 1, true);
		Texture MatIcon = Texture("Resources/Icons/sphere.png", 1, true);
		Texture ShaderIcon = Texture("Resources/Icons/shader.png", 1, true);
		Texture ModelIcon = Texture("Resources/Icons/model.png", 1, true);
		Texture UnknownIcon = Texture("Resources/Icons/unknown.png", 1, true);
		Texture SaveIcon = Texture("Resources/Icons/disk.png", 1, true);
		Texture PlayIcon = Texture("Resources/Icons/play_button.png", 1, true);
		Texture StopIcon = Texture("Resources/Icons/stop.png", 1, true);*/
	}

	UIData& UIRenderer::GetEditorUIData()
	{
		return EditorUIData;
	}
}
