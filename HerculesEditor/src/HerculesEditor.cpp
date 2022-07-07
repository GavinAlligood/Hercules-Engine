#include "HerculesEditor.h"

namespace Hercules {
	Hercules::Editor::Editor(const char* name, std::string projectPath, bool isGame)
		: Application(name, projectPath, isGame), m_ProjectPath(projectPath)
	{
		LevelManager::OpenLevel(m_CurrentLevel.c_str(), m_ProjectPath);
		SceneManager::SetBackgroundColor(0.3f, 0.3f, 0.7f);
		Camera::Init(5.0f);

		Framebuffer::Create(Application::Get().GetWindow().GetWidth(),
			Application::Get().GetWindow().GetHeight());
		
		UIRenderer::SetLevels(m_ProjectPath, m_EditorLevel, m_RuntimeLevel, m_CurrentLevel);
	}
	
	Hercules::Editor::~Editor()
	{
		Framebuffer::Destroy();

		glfwTerminate();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	//TODO: Clean this function up
	void Hercules::Editor::Input()
	{
		bool& QuickMenuCheck = UIRenderer::GetEditorUIData().QuickMenuCheck;

		if (holdingRight)
		{
			if (InputManager::IsKeyPressed(HC_KEY_W))
			{
				Camera::MoveForward(1);
			}
			else if (InputManager::IsKeyPressed(HC_KEY_S))
			{
				Camera::MoveBackward(1);
			}
			if (InputManager::IsKeyPressed(HC_KEY_A))
			{
				Camera::MoveLeft(1);
			}
			else if (InputManager::IsKeyPressed(HC_KEY_D))
			{
				Camera::MoveRight(1);
			}
			if (InputManager::IsKeyPressed(HC_KEY_SPACE))
			{
				Camera::MoveUp(1);
			}
			else if (InputManager::IsKeyPressed(HC_KEY_LEFT_ALT))
			{
				Camera::MoveDown(1);
			}
		}

		if (InputManager::IsMousePressed(HC_MOUSE_BUTTON_2))
		{
			if (m_InEditor) holdingRight = true;
		}
		else
		{
			holdingRight = false;
		}

		if (InputManager::IsMousePressed(HC_MOUSE_BUTTON_3))
		{
			if (m_InEditor) holdingMiddle = true;
		}
		else
		{
			holdingMiddle = false;
		}

		if (InputManager::IsMousePressed(HC_MOUSE_BUTTON_2) && !m_InEditor) //holdingRight because that's considered looking
		{
			if (!holdingRight)
			{
				QuickMenuCheck = true;
			}
		}
		else
		{
			QuickMenuCheck = false;
		}
	}

	void Hercules::Editor::Start()
	{
		UIRenderer::Init();
		UIRenderer::CreateIcons();
		SettingsMenu::UseStyleLightMode();
	}

	void Hercules::Editor::Update()
	{
		Camera::UpdateTime();
		Input();

		Framebuffer::Bind();
		SpatialRenderer::ClearColorBuffer(SceneManager::GetBackgroundColor());

		auto [mx, my] = ImGui::GetMousePos();

		//mx -= m_ViewportBounds[0].x;
		//my -= m_ViewportBounds[0].y;

		//TODO: Create reference to m_ViewportBounds instead of calling GetEditorUIData every time it's referenced

		mx -= UIRenderer::GetEditorUIData().m_ViewportBounds[0].x;
		my -= UIRenderer::GetEditorUIData().m_ViewportBounds[0].y;
		
		//glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
		glm::vec2 viewportSize = UIRenderer::GetEditorUIData().m_ViewportBounds[1] - UIRenderer::GetEditorUIData().m_ViewportBounds[0];
		//my *= -1;
		my = viewportSize.y - my;

		int mouseX = (int)mx;
		int mouseY = (int)my;

		//HC_CORE_TRACE("{0}:{1}", mouseX, mouseY);
		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
		{
			/*int pixelData = framebuffer.ReadPixel(1, mouseX, mouseY);
			HC_CORE_TRACE("Data: {0}", pixelData);*/
			m_InEditor = true;
		}
		else { m_InEditor = false; }


		//UI Rendering
		//UIRenderer::Render();
	}

	void Editor::ImGuiRender()
	{
		UIRenderer::Render();
	}

	void Editor::OnEvent(Event& e)
	{
		if (e.GetType() == EventType::CursorMoved)
		{
			//if (holdingMiddle)
			//{
			//	glfwSetInputMode(Application::GetWindow().GetWindow(), GLFW_CURSOR,
			//		GLFW_CURSOR_DISABLED);

			//	CursorMovedEvent& c = (CursorMovedEvent&)e;
			//	//reset position or something
			//	if (backupX > c.GetX()) { Camera::MoveRight(backupX - c.GetX()); } //backupX - c.GetX()
			//	else if (backupX < c.GetX()) { Camera::MoveLeft(c.GetX() - backupX); } //c.GetX() - backupX

			//	if (backupY > c.GetY()) { Camera::MoveDown(backupY - c.GetY()); } //backupY - c.GetY()
			//	else if (backupY < c.GetY()) { Camera::MoveUp(c.GetY() - backupY); } //c.GetY() - backupY

			//	backupX = c.GetX();
			//	backupY = c.GetY();
			//}
			if (holdingRight)
			{
				glfwSetInputMode(Application::GetWindow().GetWindow(), GLFW_CURSOR,
					GLFW_CURSOR_DISABLED);
				CursorMovedEvent& c = (CursorMovedEvent&)e;
				Camera::Look(c.GetX(), c.GetY());
			}
			else
			{
				Camera::SetFirstMouse(true);
				glfwSetInputMode(Application::GetWindow().GetWindow(), GLFW_CURSOR,
					GLFW_CURSOR_NORMAL);
			}
		}

		if (e.GetType() == EventType::MouseScrolled && m_InEditor && !holdingMiddle)
		{
			MouseScrolledEvent& m = (MouseScrolledEvent&)e;

			//HC_CORE_TRACE("{0}:{1}", m.GetX(), m.GetY());
			if (m.GetY() == 1) { Camera::MoveForward(35); }
			else if (m.GetY() == -1) { Camera::MoveBackward(35); }
		}

		if (e.GetType() == EventType::WindowResize)
		{
			WindowResizeEvent& r = (WindowResizeEvent&)e;

			Framebuffer::Destroy();
			auto& win = Application::Get().GetWindow();
			Framebuffer::Create(win.GetWidth(), win.GetHeight());
		}
	}

	void Hercules::Editor::UpdateFramebuffer()
	{
		Framebuffer::Bind();
	}

	//	//todo: make this look better
	//	//content browser
	//	//dont refresh this on everyframe, maybe make a refresh button
	//	if (ImGui::Begin("Content Browser"))
	//	{
	//		if (currentPath != std::filesystem::path(m_ProjectPath + "/Assets"))
	//		{
	//			if (ImGui::Button("<-"))
	//			{
	//				currentPath = currentPath.parent_path();
	//			}
	//		}

	//		static float padding = 10;
	//		static float thumbnailSize = 80;
	//		float cellSize = thumbnailSize + padding;

	//		float panelWidth = ImGui::GetContentRegionAvail().x;
	//		int columnCount = (int)(panelWidth / cellSize);
	//		if (columnCount < 1) columnCount = 1;

	//		ImGui::Columns(columnCount, 0, false);

	//		for (auto& i : std::filesystem::directory_iterator(currentPath))
	//		{
	//			std::filesystem::path assets = m_ProjectPath + "/Assets";
	//			const auto& path = i.path();
	//			auto relativePath = std::filesystem::relative(path, assets);
	//			std::string filenameString = relativePath.filename().string();

	//			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	//			if (i.is_directory())
	//			{
	//				ImGui::ImageButton((ImTextureID)folderIcon.GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
	//				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	//				{
	//					currentPath /= i.path().filename();
	//				}
	//				ImGui::TextWrapped(filenameString.c_str());

	//				ImGui::NextColumn();
	//			}
	//			else
	//			{
	//				//get specific ending

	//				auto extension = relativePath.extension().string();

	//				if (extension == ".txt")
	//				{
	//					ImGui::ImageButton((ImTextureID)fileIcon.GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
	//				}
	//				//add other formats
	//				else if (extension == ".png" || extension == ".jpg")
	//				{
	//					//For now ill just use a picture icon, when i work on the asset editor i will change this to a preview of the image
	//					ImGui::ImageButton((ImTextureID)imageIcon.GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
	//				}
	//				else if (extension == ".ttf" || extension == ".TTF")
	//				{
	//					ImGui::ImageButton((ImTextureID)fontIcon.GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
	//				}
	//				else if (extension == ".hcmat")
	//				{
	//					ImGui::ImageButton((ImTextureID)matIcon.GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
	//				}
	//				else if (extension == ".shader")
	//				{
	//					ImGui::ImageButton((ImTextureID)shaderIcon.GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
	//				}
	//				else if (extension == ".obj") //TODO: Add more like FBX etc
	//				{
	//					ImGui::ImageButton((ImTextureID)modelIcon.GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });

	//				}
	//				else
	//				{
	//					ImGui::ImageButton((ImTextureID)unknownIcon.GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
	//				}

	//				if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
	//				{
	//					//asset editor
	//				}
	//				ImGui::TextWrapped(filenameString.c_str());

	//				ImGui::NextColumn();
	//			}
	//			ImGui::PopStyleColor();
	//		}

	//		ImGui::Columns(1);

	//		ImGui::SliderFloat("Thumbnail size", &thumbnailSize, 16, 512);
	//		ImGui::SliderFloat("Padding", &padding, 0, 32);

	//		ImGui::End();
	//	}

	//	ImGui::End();

	//	ImGui::Render();
	//	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	//	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	//	{
	//		GLFWwindow* backup_current_context = glfwGetCurrentContext();
	//		ImGui::UpdatePlatformWindows();
	//		ImGui::RenderPlatformWindowsDefault();
	//		glfwMakeContextCurrent(backup_current_context);
	//	}
	//}

	Hercules::Application* Hercules::CreateApplication()
	{
		//isGame needs to be true because the editor uses rendering features
		return new Editor("Hercules Editor", "C:/Users/Gavin/source/repos/HerculesEngine/Hercules/DemoProject/", true);
	}
}