#include "HerculesEditor.h"

namespace Hercules {
	Hercules::Editor::Editor(const char* name, std::string projectPath, bool isGame)
		: Application(name, projectPath, isGame), m_ProjectPath(projectPath)
	{
		LevelManager::OpenLevel(m_CurrentLevel.c_str(), m_ProjectPath);
		SceneManager::SetBackgroundColor(0.3f, 0.3f, 0.7f);
		Camera::Init(5.0f);

		EditorUIRenderer = new UIRenderer();
		EditorUIRenderer->SetLevels(m_EditorLevel, m_RuntimeLevel, m_CurrentLevel);
	}

	Hercules::Editor::~Editor()
	{
		delete EditorUIRenderer;

		glfwTerminate();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Hercules::Editor::Input()
	{
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
			if (inEditor) holdingRight = true;
		}
		else
		{
			holdingRight = false;
		}

		if (InputManager::IsMousePressed(HC_MOUSE_BUTTON_3))
		{
			if (inEditor) holdingMiddle = true;
		}
		else
		{
			holdingMiddle = false;
		}

		if (InputManager::IsMousePressed(HC_MOUSE_BUTTON_2) && !inEditor) //holdingRight because that's considered looking
		{
			if (!holdingRight)
			{
				//EDitorData
				//quickMenu = true;
				UIRenderer::GetEditorUIData().QuickMenuCheck = true;
			}

		}
		else
		{
			//quickMenu = false;
			UIRenderer::GetEditorUIData().QuickMenuCheck = true;
		}

		//TODO: keyboard shortcuts
		/*if (InputManager::IsKeyPressed(HC_KEY_LEFT_CONTROL) && InputManager::IsKeyPressed(HC_KEY_A))
		{
			ImGui::OpenPopup("New Entity");
		}*/
	}

	void Hercules::Editor::Start()
	{
		EditorUIRenderer->Init();

		UseStyleLightMode();
	}

	void Hercules::Editor::Update()
	{
		Camera::UpdateTime();
		Input();

		//m_Framebuffer.Bind();
		EditorUIRenderer->GetFramebuffer().Bind();
		SpatialRenderer::ClearColorBuffer(SceneManager::GetBackgroundColor());

		auto [mx, my] = ImGui::GetMousePos();

		mx -= m_ViewportBounds[0].x;
		my -= m_ViewportBounds[0].y;

		glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
		//my *= -1;
		my = viewportSize.y - my;

		int mouseX = (int)mx;
		int mouseY = (int)my;

		//HC_CORE_TRACE("{0}:{1}", mouseX, mouseY);
		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
		{
			/*int pixelData = framebuffer.ReadPixel(1, mouseX, mouseY);
			HC_CORE_TRACE("Data: {0}", pixelData);*/
			inEditor = true;
		}
		else { inEditor = false; }


		//UI Rendering
		EditorUIRenderer->Render();
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

		if (e.GetType() == EventType::MouseScrolled && inEditor && !holdingMiddle)
		{
			MouseScrolledEvent& m = (MouseScrolledEvent&)e;

			//HC_CORE_TRACE("{0}:{1}", m.GetX(), m.GetY());
			if (m.GetY() == 1) { Camera::MoveForward(35); }
			else if (m.GetY() == -1) { Camera::MoveBackward(35); }
		}

		if (e.GetType() == EventType::WindowResize)
		{
			WindowResizeEvent& r = (WindowResizeEvent&)e;

			EditorUIRenderer->GetFramebuffer().Destroy();
			auto& win = Application::Get().GetWindow();
			EditorUIRenderer->GetFramebuffer().Create(win.GetWidth(), win.GetHeight());
		}
	}

	void Hercules::Editor::UpdateFramebuffer()
	{
		EditorUIRenderer->GetFramebuffer().Bind();
	}

	//void Hercules::Editor::ImGuiRender()
	//{
	//	EditorUIRenderer->GetFramebuffer().Unbind();
	//	ImGui_ImplOpenGL3_NewFrame();
	//	ImGui_ImplGlfw_NewFrame();
	//	ImGui::NewFrame();

	//	//ImGui::ShowDemoWindow();

	//	static bool p_open = true;
	//	static bool opt_fullscreen = true;
	//	static bool opt_padding = false;
	//	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	//	// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
	//	// because it would be confusing to have two docking targets within each others.
	//	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	//	if (opt_fullscreen)
	//	{
	//		ImGuiViewport* viewport = ImGui::GetMainViewport();
	//		ImGui::SetNextWindowPos(viewport->GetWorkPos());
	//		ImGui::SetNextWindowSize(viewport->GetWorkSize());
	//		ImGui::SetNextWindowViewport(viewport->ID);
	//		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	//		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	//		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	//		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	//	}
	//	else
	//	{
	//		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	//	}

	//	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
	//		window_flags |= ImGuiWindowFlags_NoBackground;

	//	if (!opt_padding)
	//		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	//	ImGui::Begin("DockSpace Demo", &p_open, window_flags);
	//	if (!opt_padding)
	//		ImGui::PopStyleVar();

	//	if (opt_fullscreen)
	//		ImGui::PopStyleVar(2);

	//	// DockSpace
	//	ImGuiIO& io = ImGui::GetIO();
	//	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	//	{
	//		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	//		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	//	}

	//	////Quick Menu
	//	if (quickMenu)
	//	{
	//		//ImVec2 pos = ImGui::GetCursorPos();
	//		//ImGui::SetNextWindowPos(pos);
	//		ImGui::OpenPopup("quick-menu");
	//	}
	//	if (ImGui::BeginPopup("quick-menu"))
	//	{
	//		//should this be else-if?
	//		//NOTE: Have section to add new stuff to the scene,
	//		//and have a section to add stuff to project
	//		ImGui::Text("New...");
	//		ImGui::Separator();
	//		if (ImGui::MenuItem("Empty Entity"))
	//		{
	//			std::string name = "Entity" + std::to_string(SceneManager::GetEntites().size() + 1);
	//			SceneManager::NewEntity(name);
	//			SceneManager::NewComponent(TransformComponent(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f)), SceneManager::GetEntites().size());
	//		}
	//		if (ImGui::MenuItem("Cube"))
	//		{
	//			std::string name = "Cube" + std::to_string(SceneManager::GetEntites().size() + 1);
	//			SceneManager::NewEntity(name);
	//			unsigned int size = SceneManager::GetEntites().size();
	//			SceneManager::NewComponent(MeshComponent(m_ProjectPath + "/Assets/Models/Cube3/cube.obj"), size);
	//			SceneManager::NewComponent(TransformComponent(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f)), size);
	//			SceneManager::NewComponent(MaterialComponent(SceneManager::GetTexture("Plastic"), *LevelManager::GetColor("Plastic")), size);
	//			SceneManager::GetMaterialComponent(SceneManager::GetEntites().size())->SetName("Plastic"); //i think this is neccesary so that the material in the game's save file isn't blank
	//		}
	//		if (ImGui::MenuItem("Light"))
	//		{
	//			std::string name = "Light" + SceneManager::GetEntites().size();
	//			SceneManager::NewEntity(name);
	//			SceneManager::NewComponent(TransformComponent(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f)), SceneManager::GetEntites().size());
	//		}
	//		ImGui::Separator();
	//		if (ImGui::MenuItem("Material"))
	//		{

	//		}

	//		ImGui::EndPopup();
	//	}

	//	//Menu bar
	//	if (ImGui::BeginMenuBar())
	//	{
	//		//print out stats
	//		if (ImGui::BeginMenu("File"))
	//		{
	//			if (ImGui::MenuItem("New Level"))
	//			{
	//				newLevel = true;
	//			}
	//			ImGui::Separator();

	//			if (ImGui::MenuItem("Save Level")) LevelManager::WriteLevel(currentLevel.c_str(), m_ProjectPath);
	//			ImGui::Separator();

	//			if (ImGui::MenuItem("Open Level"))
	//			{
	//				level = true;
	//			}
	//			ImGui::Separator();

	//			if (ImGui::MenuItem("Exit")) Application::Get().Close();
	//			ImGui::Separator();

	//			ImGui::EndMenu();
	//		}

	//		ImGui::EndMenuBar();
	//	}

	//	//Settings
	//	{
	//		ImGui::Begin("Settings");
	//		if (ImGui::Checkbox("Wireframe", &wireframe))
	//		{
	//			if (wireframe) { HC_VIEW_WIREFRAME; HC_STAT("Wireframe enabled"); }
	//			else { HC_VIEW_NORMAL; HC_STAT("Wireframe disabled"); }
	//		}
	//		ImGui::Checkbox("Show Performance Overlay", &showStats);

	//		ImGui::Separator();
	//		ImVec4 bgColor = ImVec4(SceneManager::GetBackgroundColor().x,
	//			SceneManager::GetBackgroundColor().y, SceneManager::GetBackgroundColor().z, 1.0f);

	//		//TODO: Save this data to scene's file
	//		//ImGui::ColorPicker3("Light Color", (float*)&color);
	//		ImGui::ColorPicker3("Background Color", (float*)&bgColor);
	//		SceneManager::SetBackgroundColor(bgColor.x, bgColor.y, bgColor.z);

	//		static int style_idx = -1;
	//		if (ImGui::Combo("Theme", &style_idx, "Light (banana)\0Dark"))
	//		{
	//			switch (style_idx)
	//			{
	//			case 0: UseStyleLightMode(); break;
	//			case 1: UseStyleDarkMode(); break;
	//			}
	//		}

	//		ImGui::End();
	//	}

	//	//Stats
	//	if (showStats)
	//	{
	//		ImGui::SetNextWindowBgAlpha(0.35f);

	//		ImGui::Begin("Performance", &showStats, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);

	//		ImGui::Text("Level: %s", currentLevel.c_str());
	//		ImGui::Text("FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//		ImGui::Text("Entities: %.1i", SceneManager::GetEntites().size());
	//		ImGui::Text("Test Components: %.1i", SceneManager::GetDemoComponentList().size());
	//		ImGui::Text("Mesh Components: %.1i", SceneManager::GetMeshComponentList().size());
	//		ImGui::Text("Transform Components: %.1i", SceneManager::GetTransformComponentList().size());
	//		ImGui::Text("Directional Lights: %.1i", SceneManager::GetDirectionalLightList().size());
	//		ImGui::Text("Point Lights: %.1i", SceneManager::GetPointLightList().size());
	//		ImGui::Text("Spot Lights: %.1i", SceneManager::GetSpotLightList().size());
	//		ImGui::Text("Textures: %.1i", SceneManager::GetTextureList().size());
	//		ImGui::Text("Material Components: %.1i", SceneManager::GetMaterialComponentList().size());
	//		ImGui::End();
	//	}

	//	//Component View
	//	{
	//		ImGui::Begin("Component View");

	//		if (selectedEntity != 0)
	//		{
	//			ImGui::Text("Entity ID: %i", selectedEntity);

	//			//ImGui::SameLine();

	//			if (ImGui::SmallButton("Add.."))
	//			{
	//				//SceneManager::NewComponent()
	//				ImGui::OpenPopup("new-component");
	//			}

	//			if (ImGui::BeginPopup("new-component"))
	//			{
	//				ImGui::Text("Create Component");
	//				if (ImGui::SmallButton("Test Component"))
	//				{
	//					if (!SceneManager::HasTestComponent(selectedEntity))
	//						SceneManager::NewComponent(DemoComponent(), selectedEntity);
	//				}
	//				if (ImGui::SmallButton("Directional Light"))
	//				{
	//					if (!SceneManager::HasLightComponent(selectedEntity))
	//						SceneManager::NewComponent(DirectionalLight(), selectedEntity);
	//				}
	//				if (ImGui::SmallButton("Point Light"))
	//				{
	//					if (!SceneManager::HasLightComponent(selectedEntity))
	//						SceneManager::NewComponent(PointLight(), selectedEntity);
	//				}
	//				if (ImGui::SmallButton("Mesh Component"))
	//				{
	//					if (!SceneManager::HasMeshComponent(selectedEntity))
	//					{
	//						if (!SceneManager::HasMaterialComponent(selectedEntity))
	//						{
	//							SceneManager::NewComponent(MaterialComponent(SceneManager::GetTexture("Plastic"), *LevelManager::GetColor("Plastic")), selectedEntity);
	//							SceneManager::GetMaterialComponent(selectedEntity)->SetName("Plastic");
	//						}
	//						SceneManager::NewComponent(MeshComponent(m_ProjectPath + "/Assets/Models/Cube3/cube.obj"), selectedEntity);
	//					}
	//				}

	//				ImGui::EndPopup();
	//			}

	//			ImGui::SameLine();

	//			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(1.0f, 0.4f, 0.3f));
	//			if (ImGui::SmallButton("Delete"))
	//			{
	//				if (SceneManager::HasTransformComponent(selectedEntity)) { SceneManager::DeleteComponent(ComponentType::Transform, selectedEntity); }
	//				if (SceneManager::HasMaterialComponent(selectedEntity)) { SceneManager::DeleteComponent(ComponentType::Material, selectedEntity); }
	//				if (SceneManager::HasTestComponent(selectedEntity)) { SceneManager::DeleteComponent(ComponentType::Test, selectedEntity); }
	//				if (SceneManager::HasDirectionalLight(selectedEntity)) { SceneManager::DeleteComponent(ComponentType::DirectionalLight, selectedEntity); }
	//				if (SceneManager::HasPointLight(selectedEntity)) { SceneManager::DeleteComponent(ComponentType::PointLight, selectedEntity); }
	//				if (SceneManager::HasSpotLight(selectedEntity)) { SceneManager::DeleteComponent(ComponentType::SpotLight, selectedEntity); }
	//				//might need to move this
	//				if (SceneManager::HasMeshComponent(selectedEntity)) { SceneManager::DeleteComponent(ComponentType::Mesh, selectedEntity); }

	//				SceneManager::DeleteEntity(selectedEntity);

	//				for (auto& i : SceneManager::GetEntites())
	//				{
	//					if (i.first > selectedEntity)
	//					{
	//						auto id = SceneManager::GetEntites().extract(i.first);
	//						id.key() = i.first - 1;
	//						SceneManager::GetEntites().insert(std::move(id));
	//					}
	//				}

	//				for (auto& i : SceneManager::GetTransformComponentList())
	//				{
	//					if (i.first > selectedEntity)
	//					{
	//						auto id = SceneManager::GetTransformComponentList().extract(i.first);
	//						id.key() = i.first - 1;
	//						SceneManager::GetTransformComponentList().insert(std::move(id));
	//					}
	//				}

	//				for (auto& i : SceneManager::GetMaterialComponentList())
	//				{
	//					if (i.first > selectedEntity)
	//					{
	//						auto id = SceneManager::GetMaterialComponentList().extract(i.first);
	//						id.key() = i.first - 1;
	//						SceneManager::GetMaterialComponentList().insert(std::move(id));
	//					}
	//				}

	//				for (auto& i : SceneManager::GetDemoComponentList())
	//				{
	//					if (i.first > selectedEntity)
	//					{
	//						auto id = SceneManager::GetDemoComponentList().extract(i.first);
	//						id.key() = i.first - 1;
	//						SceneManager::GetDemoComponentList().insert(std::move(id));
	//					}
	//				}

	//				for (auto& i : SceneManager::GetDirectionalLightList())
	//				{
	//					if (i.first > selectedEntity)
	//					{
	//						auto id = SceneManager::GetDirectionalLightList().extract(i.first);
	//						id.key() = i.first - 1;
	//						SceneManager::GetDirectionalLightList().insert(std::move(id));
	//					}
	//				}

	//				for (auto& i : SceneManager::GetMeshComponentList())
	//				{
	//					if (i.first > selectedEntity)
	//					{
	//						auto id = SceneManager::GetMeshComponentList().extract(i.first);
	//						id.key() = i.first - 1;
	//						SceneManager::GetMeshComponentList().insert(std::move(id));
	//					}
	//				}

	//				//TODO: Spot light

	//				//TODO: Point light

	//				/*for (auto& i : SceneManager::GetEntites())
	//				{
	//					HC_CORE_TRACE(i.first);
	//				}*/

	//				selectedEntity = 0;
	//			}
	//			ImGui::PopStyleColor();
	//		}

	//		if (hasLight)
	//		{
	//			if (SceneManager::HasDirectionalLight(selectedEntity))
	//			{
	//				if (ImGui::Begin("Light Component", &hasLight))
	//				{
	//					//seperator
	//					ImGui::Text("Light Component");

	//					ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	//					color.x = SceneManager::GetDirectionalLightComponent(selectedEntity)->GetColor().x;
	//					color.y = SceneManager::GetDirectionalLightComponent(selectedEntity)->GetColor().y;
	//					color.z = SceneManager::GetDirectionalLightComponent(selectedEntity)->GetColor().z;
	//					float ambient = SceneManager::GetDirectionalLightComponent(selectedEntity)->GetAmbient();

	//					ImGui::ColorPicker3("Light Color", (float*)&color);
	//					ImGui::DragFloat("Ambient", &ambient, 0.1f, 0.0f, 0.0f, "%.2f");

	//					SceneManager::GetDirectionalLightComponent(selectedEntity)->SetColor(glm::vec3(color.x, color.y, color.z));
	//					SceneManager::GetDirectionalLightComponent(selectedEntity)->SetAmbient(ambient);

	//					if (ImGui::SmallButton("Delete"))
	//					{
	//						SceneManager::DeleteComponent(ComponentType::Light, selectedEntity);
	//					}

	//					ImGui::End();
	//				}
	//				else
	//				{
	//					ImGui::End();
	//				}
	//			}
	//		}

	//		if (hasTest)
	//		{
	//			if (SceneManager::HasTestComponent(selectedEntity))
	//			{
	//				if (ImGui::Begin("Test Component", &hasTest))
	//				{
	//					ImGui::Text("Test component");

	//					if (ImGui::SmallButton("Delete"))
	//					{
	//						SceneManager::DeleteComponent(ComponentType::Test, selectedEntity);
	//					}

	//					ImGui::End();
	//				}
	//				else
	//				{
	//					ImGui::End();
	//				}
	//			}
	//		}

	//		if (hasTransform)
	//		{
	//			if (SceneManager::HasTransformComponent(selectedEntity))
	//			{
	//				if (ImGui::Begin("Transform Component", &hasTransform))
	//				{
	//					float xPos = SceneManager::GetTransformComponent(selectedEntity)->GetPos().x;
	//					float yPos = SceneManager::GetTransformComponent(selectedEntity)->GetPos().y;
	//					float zPos = SceneManager::GetTransformComponent(selectedEntity)->GetPos().z;

	//					ImGui::Text("Position");
	//					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(1.0f, 0.4f, 0.3f));
	//					ImGui::Button("X"); ImGui::SameLine();
	//					ImGui::DragFloat("##Xpos", &xPos, 0.1f, 0.0f, 0.0f, "%.2f");
	//					ImGui::PopStyleColor();

	//					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0.7f, 1.0f, 0.4f));
	//					ImGui::Button("Y"); ImGui::SameLine();
	//					ImGui::DragFloat("##Ypos", &yPos, 0.1f, 0.0f, 0.0f, "%.2f");
	//					ImGui::PopStyleColor();

	//					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0.4f, 0.7f, 1.0f));
	//					ImGui::Button("Z"); ImGui::SameLine();
	//					ImGui::DragFloat("##Zpos", &zPos, 0.1f, 0.0f, 0.0f, "%.2f");
	//					ImGui::PopStyleColor();

	//					float xScale = SceneManager::GetTransformComponent(selectedEntity)->GetScale().x;
	//					float yScale = SceneManager::GetTransformComponent(selectedEntity)->GetScale().y;
	//					float zScale = SceneManager::GetTransformComponent(selectedEntity)->GetScale().z;

	//					ImGui::Text("Scale");
	//					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(1.0f, 0.4f, 0.3f));
	//					ImGui::Button("X"); ImGui::SameLine();
	//					ImGui::DragFloat("##Xwidth", &xScale, 0.1f, 0.0f, 0.0f, "%.2f");
	//					ImGui::PopStyleColor();

	//					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0.7f, 1.0f, 0.4f));
	//					ImGui::Button("Y"); ImGui::SameLine();
	//					ImGui::DragFloat("##Ywidth", &yScale, 0.1f, 0.0f, 0.0f, "%.2f");
	//					ImGui::PopStyleColor();

	//					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0.4f, 0.7f, 1.0f));
	//					ImGui::Button("Z"); ImGui::SameLine();
	//					ImGui::DragFloat("##Zwidth", &zScale, 0.1f, 0.0f, 0.0f, "%.2f");
	//					ImGui::PopStyleColor();

	//					float xRot = SceneManager::GetTransformComponent(selectedEntity)->GetRotation().x;
	//					float yRot = SceneManager::GetTransformComponent(selectedEntity)->GetRotation().y;
	//					float zRot = SceneManager::GetTransformComponent(selectedEntity)->GetRotation().z;

	//					ImGui::Text("Rotation");
	//					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(1.0f, 0.4f, 0.3f));
	//					ImGui::Button("X"); ImGui::SameLine();
	//					ImGui::DragFloat("##Xrot", &xRot, 0.1f, 0.0f, 0.0f, "%.2f");
	//					ImGui::PopStyleColor();

	//					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0.7f, 1.0f, 0.4f));
	//					ImGui::Button("Y"); ImGui::SameLine();
	//					ImGui::DragFloat("##Yrot", &yRot, 0.1f, 0.0f, 0.0f, "%.2f");
	//					ImGui::PopStyleColor();

	//					ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0.4f, 0.7f, 1.0f));
	//					ImGui::Button("Z"); ImGui::SameLine();
	//					ImGui::DragFloat("##Zrot", &zRot, 0.1f, 0.0f, 0.0f, "%.2f");
	//					ImGui::PopStyleColor();

	//					SceneManager::GetTransformComponent(selectedEntity)->SetPos(glm::vec3(xPos, yPos, zPos));
	//					SceneManager::GetTransformComponent(selectedEntity)->SetScale(glm::vec3(xScale, yScale, zScale));
	//					SceneManager::GetTransformComponent(selectedEntity)->SetRotation(glm::vec3(xRot, yRot, zRot));
	//					ImGui::End();
	//				}
	//				else
	//				{
	//					ImGui::End();
	//				}
	//			}
	//		}

	//		if (level)
	//		{
	//			ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	//			ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	//			ImGui::SetNextWindowSize(ImVec2{ 400,400 });
	//			ImGui::OpenPopup("Levels");

	//			if (ImGui::BeginPopupModal("Levels", &level, ImGuiWindowFlags_AlwaysAutoResize))
	//			{
	//				ImGui::Text("Select level								 ");
	//				for (auto& i : std::filesystem::directory_iterator(m_ProjectPath + "Levels"))
	//				{
	//					std::string name = i.path().filename().string().substr(0,
	//						i.path().filename().string().find("."));
	//					if (ImGui::MenuItem(name.c_str()))
	//					{
	//						currentLevel = m_ProjectPath + "Levels/" + name + ".hclvl";
	//						LevelManager::OpenLevel(currentLevel.c_str(), m_ProjectPath);

	//						ImGui::CloseCurrentPopup();
	//						level = false;
	//					}
	//				}

	//				ImGui::EndPopup();
	//			}
	//		}

	//		if (newLevel)
	//		{
	//			ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	//			ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	//			ImGui::OpenPopup("New Level");

	//			if (ImGui::BeginPopupModal("New Level", NULL, ImGuiWindowFlags_AlwaysAutoResize))
	//			{
	//				static char levelname[32] = "";

	//				ImGui::Text("Enter Level Name: ");
	//				ImGui::InputText("##levelName", levelname, IM_ARRAYSIZE(levelname));

	//				ImGui::SameLine();

	//				if (ImGui::SmallButton("Create"))
	//				{
	//					LevelManager::NewLevel(levelname);
	//					LevelManager::OpenLevel(levelname, m_ProjectPath);
	//					currentLevel = levelname;
	//					ImGui::CloseCurrentPopup();
	//					newLevel = false;
	//				}
	//				ImGui::SameLine();
	//				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(1.0f, 0.4f, 0.3f));
	//				if (ImGui::SmallButton("Cancel"))
	//				{
	//					newLevel = false;
	//					ImGui::CloseCurrentPopup();
	//				}
	//				ImGui::PopStyleColor();
	//				ImGui::EndPopup();
	//			}
	//		}

	//		if (hasMaterial)
	//		{
	//			if (SceneManager::HasMaterialComponent(selectedEntity))
	//			{
	//				if (ImGui::Begin("Material", &hasMaterial))
	//				{
	//					ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	//					color.x = SceneManager::GetMaterialComponent(selectedEntity)->GetColor().x;
	//					color.y = SceneManager::GetMaterialComponent(selectedEntity)->GetColor().y;
	//					color.z = SceneManager::GetMaterialComponent(selectedEntity)->GetColor().z;

	//					float shininess = SceneManager::GetMaterialComponent(selectedEntity)->GetShininess();

	//					ImGui::ColorPicker3("Select Material", (float*)&color);

	//					ImGui::DragFloat("Shininess", &shininess, 0.1f, 2.0f, 256.0f, "%.2f");

	//					SceneManager::GetMaterialComponent(selectedEntity)->SetShininess(shininess);
	//					SceneManager::GetMaterialComponent(selectedEntity)->SetColor(glm::vec3(color.x, color.y, color.z));

	//					if (ImGui::SmallButton("Material"))
	//					{
	//						ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	//						ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	//						//ImGui::OpenPopup("Select Material");
	//						ImGui::OpenPopup("Material Select");
	//					}

	//					bool p_opened = true;

	//					if (ImGui::BeginPopupModal("Material Select", &p_opened, ImGuiWindowFlags_NoResize))
	//					{
	//						for (auto& i : std::filesystem::directory_iterator(m_ProjectPath + "/Assets/Materials"))
	//						{
	//							std::string name = i.path().filename().string().substr(0,
	//								i.path().filename().string().find("."));

	//							std::filesystem::path assets = m_ProjectPath + "/Assets/Materials";
	//							const auto& path = i.path();
	//							auto relativePath = std::filesystem::relative(path, assets);
	//							auto extension = relativePath.extension().string();
	//							if (extension == ".hcmat")
	//							{
	//								if (ImGui::Button(name.c_str()))
	//								{
	//									auto m = SceneManager::GetMaterialComponent(selectedEntity);
	//									SceneManager::SetTextureByName(selectedEntity, name.c_str());
	//									m->SetColor(*LevelManager::GetColor(name));
	//									m->SetShininess(*LevelManager::GetShininess(name));
	//									m->SetName(name);
	//									ImGui::CloseCurrentPopup();
	//								}
	//							}
	//						}

	//						ImGui::EndPopup();
	//					}

	//					ImGui::SameLine();
	//					ImGui::Image((void*)SceneManager::GetMaterialComponent(selectedEntity)->GetTexture()->GetID(), ImVec2{ 50, 50 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	//					ImGui::End();
	//				}
	//				else
	//				{
	//					ImGui::End();
	//				}
	//			}
	//		}

	//		if (hasMesh)
	//		{
	//			if (SceneManager::HasMeshComponent(selectedEntity))
	//			{
	//				if (ImGui::Begin("Mesh", &hasMesh))
	//				{
	//					ImGui::Text("Mesh: %s", SceneManager::GetMeshComponent(selectedEntity)->GetPath().c_str());

	//					if (ImGui::Button("Open..."))
	//					{
	//						ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	//						ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	//						ImGui::OpenPopup("Mesh Select");
	//					}

	//					bool p_opened = true;

	//					if (ImGui::BeginPopupModal("Mesh Select", &p_opened, ImGuiWindowFlags_NoResize)) //AutoResize
	//					{
	//						//This will be drag and drop eventually
	//						//Small browser

	//						static std::filesystem::path currentPopupPath = m_ProjectPath + "/Assets/Models";

	//						if (currentPopupPath != std::filesystem::path(m_ProjectPath + "/Assets/Models"))
	//						{
	//							if (ImGui::Button("<-"))
	//							{
	//								currentPopupPath = currentPopupPath.parent_path();
	//							}
	//						}

	//						for (auto& i : std::filesystem::directory_iterator(currentPopupPath))
	//						{
	//							std::string name = i.path().filename().string().substr(0,
	//								i.path().filename().string().find("."));
	//							if (i.is_directory())
	//							{
	//								if (ImGui::Button(name.c_str()))
	//								{
	//									currentPopupPath /= i.path().filename();
	//								}
	//							}
	//							else
	//							{
	//								std::filesystem::path assets = m_ProjectPath + "/Assets/Models";
	//								const auto& path = i.path();
	//								auto relativePath = std::filesystem::relative(path, assets);
	//								auto extension = relativePath.extension().string();

	//								if (extension == ".obj")
	//								{
	//									if (ImGui::Button(name.c_str()))
	//									{
	//										SceneManager::GetMeshComponent(selectedEntity)->GetModel().ResetMesh();
	//										SceneManager::GetMeshComponent(selectedEntity)->GetModel().loadModel(path.string());
	//										SceneManager::GetMeshComponent(selectedEntity)->SetPath(path.string());
	//										ImGui::CloseCurrentPopup();
	//									}
	//								}
	//							}

	//						}
	//						ImGui::EndPopup();
	//					}

	//					if (ImGui::Button("Delete"))
	//					{
	//						SceneManager::DeleteComponent(ComponentType::Mesh, selectedEntity);
	//					}
	//				}
	//				else
	//				{
	//					ImGui::End();
	//				}

	//				ImGui::End();
	//			}
	//		}

	//		ImGui::End();
	//	}

	//	//Toolbar
	//	{
	//		ImGui::Begin("Toolbar");

	//		static float padding = 10;
	//		static float thumbnailSize = 30;
	//		float cellSize = thumbnailSize + padding;

	//		float panelWidth = ImGui::GetContentRegionAvail().x;
	//		int columnCount = (int)(panelWidth / cellSize);
	//		if (columnCount < 1) columnCount = 1;

	//		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	//		ImGui::Columns(columnCount, 0, false);

	//		//Save button
	//		if (ImGui::ImageButton((ImTextureID)saveIcon.GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 }))
	//		{
	//			LevelManager::WriteLevel(currentLevel.c_str(), m_ProjectPath);
	//		}
	//		ImGui::NextColumn();

	//		//Play scene
	//		//TODO: Disable other buttons (save, etc)
	//		if (ImGui::ImageButton((ImTextureID)playIcon.GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 }))
	//		{
	//			/*
	//			1. Create duplicate scene
	//			2. Run that scene
	//			3. When ending the scene, restore current scene to previous one
	//			*/
	//			LevelManager::WriteLevel(currentLevel.c_str(), m_ProjectPath); //Save the level and the runtime level so that the runtime level is actually up to date
	//			LevelManager::WriteLevel(runtimeLevel.c_str(), m_ProjectPath);
	//			currentLevel = runtimeLevel;
	//			runningInEditor = true;
	//			LevelManager::OpenLevel(currentLevel.c_str(), m_ProjectPath); //runtimeLevel
	//		}
	//		ImGui::NextColumn();

	//		if (runningInEditor)
	//		{
	//			if (ImGui::ImageButton((ImTextureID)stopIcon.GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 }))
	//			{
	//				currentLevel = editorLevel;
	//				runningInEditor = false;
	//				LevelManager::OpenLevel(currentLevel.c_str(), m_ProjectPath); //editorLevel
	//			}
	//		}

	//		ImGui::PopStyleColor();
	//		ImGui::End();
	//	}

	//	//////Viewport
	//	{
	//		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
	//		//Check, ImGUiWIndowFlags_unsaveddocument
	//		ImGui::Begin("Scene");

	//		ImVec2 viewSize = ImGui::GetContentRegionAvail();
	//		m_ViewportSize.x = viewSize.x;
	//		m_ViewportSize.y = viewSize.y;
	//		Camera::SetAspectRatio(viewSize.x, viewSize.y);
	//		Camera::UpdateAspectRatio();

	//		//HC_CORE_TRACE(framebuffer.GetIntBuffer());
	//		ImGui::Image((void*)EditorUIRenderer->GetFramebuffer().GetColorBuffer(), viewSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

	//		auto viewportOffset = ImGui::GetCursorPos();
	//		auto windowSize = ImGui::GetWindowSize();
	//		ImVec2 minBound = ImGui::GetWindowPos();
	//		minBound.x += viewportOffset.x;
	//		viewportOffset.y -= minBound.y;

	//		ImVec2 maxBound = { minBound.x + windowSize.x, minBound.y + windowSize.y };
	//		m_ViewportBounds[0] = { minBound.x, minBound.y };
	//		m_ViewportBounds[1] = { maxBound.x, maxBound.y };

	//		ImGui::End();
	//		ImGui::PopStyleVar();
	//	}

	//	//Scene hierarchy
	//	{
	//		ImGui::Begin("Scene Components");

	//		if (ImGui::MenuItem("New Entity"))
	//		{
	//			ImGui::OpenPopup("New Entity");
	//		}

	//		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	//		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

	//		bool p_opened = true;

	//		if (ImGui::BeginPopupModal("New Entity", &p_opened, ImGuiWindowFlags_AlwaysAutoResize))
	//		{
	//			ImGui::Text("Enter Entity Name: ");
	//			ImGui::InputText("##Name", name, IM_ARRAYSIZE(name));

	//			ImGui::SameLine();

	//			//TODO: Make a check to ensure there aren't duplicate entity names
	//			if (ImGui::SmallButton("Create"))
	//			{
	//				SceneManager::NewEntity((std::string)name);
	//				//Automatic components entities have by default
	//				unsigned int size = SceneManager::GetEntites().size();
	//				SceneManager::NewComponent(MeshComponent(m_ProjectPath + "/Assets/Models/Cube3/cube.obj"), size);
	//				SceneManager::NewComponent(TransformComponent(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f)), size);
	//				SceneManager::NewComponent(MaterialComponent(SceneManager::GetTexture("Plastic"), *LevelManager::GetColor("Plastic")), size);
	//				SceneManager::GetMaterialComponent(SceneManager::GetEntites().size())->SetName("Plastic"); //wait why am i doing this?
	//				HC_INFO("Created new entity: {0}", name);
	//				memset(name, 0, sizeof(name)); // Reset name
	//				ImGui::CloseCurrentPopup();
	//			}
	//			ImGui::SameLine();
	//			ImGui::EndPopup();
	//		}

	//		std::map<unsigned int, std::string>::iterator it;
	//		for (it = SceneManager::GetEntites().begin();
	//			it != SceneManager::GetEntites().end(); ++it)
	//		{
	//			//icon
	//			if (ImGui::TreeNode((void*)(intptr_t)(*it).first, "%s", (*it).second.c_str()))
	//			{
	//				//Might end up changing slightly in future
	//				ImGui::SameLine();

	//				if (ImGui::SmallButton("Edit"))
	//				{
	//					selectedEntity = (*it).first;
	//				}

	//				if (SceneManager::HasTransformComponent((*it).first))
	//				{
	//					if (ImGui::Button("Transform Component"))
	//					{
	//						selectedEntity = (*it).first;
	//						hasTransform = true;
	//					}
	//				}

	//				if (SceneManager::HasLightComponent((*it).first))
	//				{
	//					if (ImGui::Button("Light Component"))
	//					{
	//						selectedEntity = (*it).first;
	//						hasLight = true;
	//					}
	//				}

	//				if (SceneManager::HasDirectionalLight((*it).first))
	//				{
	//					if (ImGui::Button("Directional Light"))
	//					{
	//						selectedEntity = (*it).first;
	//						//hasDirectional = true;
	//						hasLight = true;
	//					}
	//				}


	//				if (SceneManager::HasPointLight((*it).first))
	//				{
	//					if (ImGui::Button("Point Light"))
	//					{
	//						selectedEntity = (*it).first;
	//						hasLight = true;
	//					}
	//				}

	//				if (SceneManager::HasTestComponent((*it).first))
	//				{
	//					if (ImGui::Button("Test Component"))
	//					{
	//						selectedEntity = (*it).first;
	//						hasTest = true;
	//					}
	//				}

	//				if (SceneManager::HasMaterialComponent((*it).first))
	//				{
	//					if (ImGui::Button("Material Component"))
	//					{
	//						selectedEntity = (*it).first;
	//						hasMaterial = true;
	//					}
	//				}

	//				if (SceneManager::HasMeshComponent((*it).first))
	//				{
	//					if (ImGui::Button("Mesh Component"))
	//					{
	//						selectedEntity = (*it).first;
	//						hasMesh = true;
	//					}
	//				}

	//				ImGui::TreePop();
	//			}
	//		}
	//		ImGui::End();
	//	}

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

	void Hercules::Editor::UseStyleLightMode()
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

	void Hercules::Editor::UseStyleDarkMode()
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

	Hercules::Application* Hercules::CreateApplication()
	{
		//isGame needs to be true because the editor uses rendering features
		return new Editor("Hercules Editor", "C:/Users/Gavin/source/repos/HerculesEngine/Hercules/DemoProject/", true);
	}
}