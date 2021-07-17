#include <../Hercules.h>

//Note: framebuffer throws error on minimize, not a big deal though (i think)
//TODO: Add help markers
//TODO: SpotLight still needs work

//NOTE: Dont forget that when you create a new component you need to add its entry to the AddComponents function in scenemanager

#define IMGUI_DEFINE_MATH_OPERATORS

namespace Hercules {

	class Editor : public Hercules::Application
	{
	public:
		Editor()
		{
			SceneManager::NewTexture("Default", "Assets/Textures/default_texture.jpg");
			SceneManager::NewTexture("Default2", "Assets/Textures/dirtMinecraft.jpg");
			SpatialRenderer::Init();
			Camera::Init(5.0f);
			LoadEntities();
		}

		~Editor()
		{
			SpatialRenderer::End();
			glfwTerminate();
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}

		//need work
		void Input()
		{
			if (holdingRight)
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
			}
			
			if (InputManager::IsMousePressed(HC_MOUSE_BUTTON_2))
			{
				holdingRight = true;
			}
			else
			{
				holdingRight = false;
			}

			//keyboard shortcuts
			/*if (InputManager::IsKeyPressed(HC_KEY_LEFT_CONTROL) && InputManager::IsKeyPressed(HC_KEY_A))
			{
				ImGui::OpenPopup("New Entity");
			}*/
		}

		void Editor::Start() override
		{
			HC_INFO("Start");
		}

		void Editor::Update() override
		{
			Camera::UpdateTime();

			Input();
		}

		void OnEvent(Event& e) override
		{
			if (e.GetType() == EventType::CursorMoved && holdingRight)
			{
				CursorMovedEvent& c = (CursorMovedEvent&)e;

				//ImGui::SetCursorScreenPos(ImVec2(centerX, centerY));

				//This is driving me insane but i have no clue how to fix it
				Camera::Look(c.GetX(), c.GetY());
			}

			if (e.GetType() == EventType::WindowResize)
			{
				WindowResizeEvent& r = (WindowResizeEvent&)e;

				centerX = Application::Get().GetWindow().GetWidth() / 2;
				centerY = Application::Get().GetWindow().GetHeight() / 2;

				framebuffer.Destroy();
				framebuffer.Create(Application::Get().GetWindow());
			}
		}

		void Editor::UpdateFramebuffer()
		{
			framebuffer.Bind();
			glEnable(GL_DEPTH_TEST);
		}

		void Editor::ImGuiRender()
		{
			framebuffer.Unbind();
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
			}

			//Settings
			{
				ImGui::Begin("Settings");
				ImGui::Checkbox("Wireframe", &wireframe);
				ImGui::Checkbox("Show Performance Overlay", &showStats);

				if (wireframe)
				{
					HC_VIEW_WIREFRAME;
				}
				else
				{
					HC_VIEW_NORMAL;
				}

				ImGui::End();
			}

			//Stats
			{
				if (showStats)
				{
					ImGui::SetNextWindowBgAlpha(0.35f);

					ImGui::Begin("Performance", &showStats, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);

					ImGui::Text("FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
					ImGui::Text("Entities: %.1i", SceneManager::GetEntites().size());
					ImGui::Text("Test Components: %.1i", SceneManager::GetDemoComponentList().size());
					ImGui::Text("Mesh Components: %.1i", SceneManager::GetMeshComponentList().size());
					ImGui::Text("Transform Components: %.1i", SceneManager::GetTransformComponentList().size());
					ImGui::Text("Directional Lights: %.1i", SceneManager::GetDirectionalLightList().size());
					ImGui::Text("Point Lights: %.1i", SceneManager::GetPointLightList().size());
					ImGui::Text("Spot Lights: %.1i", SceneManager::GetSpotLightList().size());
					ImGui::Text("Material Components: %.1i", SceneManager::GetMaterialComponentList().size());
					ImGui::End();
				}
			}

			//Component View
			{
				ImGui::Begin("Component View");

				if (selectedEntity != 0)
				{
					ImGui::Text("Entity ID: %i", selectedEntity);

					ImGui::SameLine();

					if (ImGui::SmallButton("Add.."))
					{
						//SceneManager::NewComponent()
						ImGui::OpenPopup("new-component");
					}

					if (ImGui::BeginPopup("new-component"))
					{
						ImGui::Text("Create Component");
						if (ImGui::SmallButton("Test Component"))
						{
							if (!SceneManager::HasTestComponent(selectedEntity))
								SceneManager::NewComponent(DemoComponent(), selectedEntity);
						}
						if (ImGui::SmallButton("Directional Light"))
						{
							if (!SceneManager::HasLightComponent(selectedEntity))
								SceneManager::NewComponent(DirectionalLight(), selectedEntity);
						}
						if (ImGui::SmallButton("Point Light"))
						{
							if (!SceneManager::HasLightComponent(selectedEntity))
								SceneManager::NewComponent(PointLight(), selectedEntity);
						}
						ImGui::EndPopup();
					}
				}

				if (hasLight)
				{
					if (SceneManager::HasLightComponent(selectedEntity))
					{
						if (ImGui::Begin("Light Component", &hasLight))
						{
							//seperator
							ImGui::Text("Light Component");

							ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
							color.x = SceneManager::GetLightComponent(selectedEntity)->GetColor().x;
							color.y = SceneManager::GetLightComponent(selectedEntity)->GetColor().y;
							color.z = SceneManager::GetLightComponent(selectedEntity)->GetColor().z;
							float ambient = SceneManager::GetLightComponent(selectedEntity)->GetAmbient();

							ImGui::ColorPicker3("Light Color", (float*)&color);
							ImGui::DragFloat("Ambient", &ambient, 0.1f, 0.0f, 0.0f, "%.2f");

							SceneManager::GetLightComponent(selectedEntity)->SetColor(glm::vec3(color.x, color.y, color.z));
							SceneManager::GetLightComponent(selectedEntity)->SetAmbient(ambient);

							if (ImGui::SmallButton("Delete"))
							{
								SceneManager::DeleteComponent(ComponentType::Light, selectedEntity);
							}

							ImGui::End();
						}
						else
						{
							ImGui::End();
						}
					}
				}
				
				if (hasTest)
				{
					if (SceneManager::HasTestComponent(selectedEntity))
					{
						if (ImGui::Begin("Test Component", &hasTest))
						{
							ImGui::Text("Test component");

							if (ImGui::SmallButton("Delete"))
							{
								SceneManager::DeleteComponent(ComponentType::Test, selectedEntity);
							}

							ImGui::End();
						}
						else
						{
							ImGui::End();
						}
					}
				}

				if (hasTransform)
				{
					if (SceneManager::HasTransformComponent(selectedEntity))
					{
						if (ImGui::Begin("Transform Component", &hasTransform))
						{
							float xPos = SceneManager::GetTransformComponent(selectedEntity)->GetPos().x;
							float yPos = SceneManager::GetTransformComponent(selectedEntity)->GetPos().y;
							float zPos = SceneManager::GetTransformComponent(selectedEntity)->GetPos().z;

							ImGui::Text("Position");
							ImGui::DragFloat("X Position", &xPos, 0.1f, 0.0f, 0.0f, "%.2f");
							ImGui::DragFloat("Y Position", &yPos, 0.1f, 0.0f, 0.0f, "%.2f");
							ImGui::DragFloat("Z Position", &zPos, 0.1f, 0.0f, 0.0f, "%.2f");

							float xScale = SceneManager::GetTransformComponent(selectedEntity)->GetScale().x;
							float yScale = SceneManager::GetTransformComponent(selectedEntity)->GetScale().y;
							float zScale = SceneManager::GetTransformComponent(selectedEntity)->GetScale().z;

							ImGui::Text("Scale");
							ImGui::DragFloat("X Width", &xScale, 0.1f, 0.0f, 0.0f, "%.2f");
							ImGui::DragFloat("Y Height", &yScale, 0.1f, 0.0f, 0.0f, "%.2f");
							ImGui::DragFloat("Z Length", &zScale, 0.1f, 0.0f, 0.0f, "%.2f");

							float xRot = SceneManager::GetTransformComponent(selectedEntity)->GetRotation().x;
							float yRot = SceneManager::GetTransformComponent(selectedEntity)->GetRotation().y;
							float zRot = SceneManager::GetTransformComponent(selectedEntity)->GetRotation().z;

							ImGui::Text("Rotation");
							ImGui::DragFloat("X Rotation", &xRot, 0.1f, 0.0f, 0.0f, "%.2f");
							ImGui::DragFloat("Y Rotation", &yRot, 0.1f, 0.0f, 0.0f, "%.2f");
							ImGui::DragFloat("Z Rotation", &zRot, 0.1f, 0.0f, 0.0f, "%.2f");

							SceneManager::GetTransformComponent(selectedEntity)->SetPos(glm::vec3(xPos, yPos, zPos));
							SceneManager::GetTransformComponent(selectedEntity)->SetScale(glm::vec3(xScale, yScale, zScale));
							SceneManager::GetTransformComponent(selectedEntity)->SetRotation(glm::vec3(xRot, yRot, zRot));
							ImGui::End();
						}
						else
						{
							ImGui::End();
						}
					}
				}

				if (hasMaterial)
				{
					if (SceneManager::HasMaterialComponent(selectedEntity))
					{
						if (ImGui::Begin("Material", &hasMaterial))
						{
							ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
							color.x = SceneManager::GetMaterialComponent(selectedEntity)->GetColor().x;
							color.y = SceneManager::GetMaterialComponent(selectedEntity)->GetColor().y;
							color.z = SceneManager::GetMaterialComponent(selectedEntity)->GetColor().z;

							float shininess = SceneManager::GetMaterialComponent(selectedEntity)->GetShininess();

							ImGui::ColorPicker3("Object Color", (float*)&color);

							ImGui::DragFloat("Shininess", &shininess, 0.1f, 2.0f, 256.0f, "%.2f");

							SceneManager::GetMaterialComponent(selectedEntity)->SetShininess(shininess);
							SceneManager::GetMaterialComponent(selectedEntity)->SetColor(glm::vec3(color.x, color.y, color.z));

							if (ImGui::SmallButton("Texture"))
							{
								ImVec2 center = ImGui::GetMainViewport()->GetCenter();
								ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
								ImGui::OpenPopup("Open Texture");	
							}

							if (ImGui::BeginPopupModal("Open Texture", NULL, ImGuiWindowFlags_AlwaysAutoResize))
							{
								std::map<const char*, Texture>::iterator it;
								for (it = SceneManager::GetTextureList().begin();
									it != SceneManager::GetTextureList().end(); ++it)
								{
									if (ImGui::MenuItem((*it).first))
									{
										SceneManager::GetMaterialComponent(selectedEntity)->SetTexture(&(*it).second);
									}
								}

								ImGui::EndPopup();
							}

							ImGui::SameLine();
							ImGui::Image((void*)SceneManager::GetMaterialComponent(selectedEntity)->GetTexture()->GetID(), ImVec2{ 50, 50 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

							ImGui::End();
						}
						else
						{
							ImGui::End();
						}
					}
				}

				ImGui::End();
			}

			////'viewport'
			{
				ImGui::Begin("Scene");
				ImVec2 viewportSize = ImGui::GetContentRegionAvail();
				Camera::SetAspectRatio(viewportSize.x, viewportSize.y);
				Camera::UpdateAspectRatio();

				ImGui::Image((void*)framebuffer.GetColorBuffer(), viewportSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

				ImGui::End();
			}

			//Scene hierarchy
			{
				ImGui::Begin("Scene Components");

				if (ImGui::MenuItem("New Entity"))
				{
					ImGui::OpenPopup("New Entity");
				}

				ImVec2 center = ImGui::GetMainViewport()->GetCenter();
				ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

				if (ImGui::BeginPopupModal("New Entity", NULL, ImGuiWindowFlags_AlwaysAutoResize))
				{
					ImGui::Text("Enter Entity Name: ");
					ImGui::InputText("##Name", name, IM_ARRAYSIZE(name));

					ImGui::SameLine();

					//TODO: Make a check to ensure there aren't duplicate entity names
					if (ImGui::SmallButton("Create"))
					{
						SceneManager::NewEntity((std::string)name);
						//Automatic components entities have by default
						SceneManager::NewComponent(TransformComponent(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), *SceneManager::GetTexture("Default"), glm::vec4(HC_COLOR_WHITE)), SceneManager::GetEntites().size());
						SceneManager::NewComponent(MaterialComponent(SceneManager::GetTexture("Default")), SceneManager::GetEntites().size());
						memset(name, 0, sizeof(name));
						ImGui::CloseCurrentPopup();
					}
					ImGui::EndPopup();
				}

				std::map<unsigned int, std::string>::iterator it;
				for (it = SceneManager::GetEntites().begin();
					it != SceneManager::GetEntites().end(); ++it)
				{
					if (ImGui::TreeNode((void*)(intptr_t)(*it).first, "%s", (*it).second.c_str()))
					{
						//Might end up changing slightly in future
						ImGui::SameLine();

						if (ImGui::SmallButton("Edit"))
						{
							selectedEntity = (*it).first;
						}

						if (SceneManager::HasTransformComponent((*it).first))
						{
							if (ImGui::Button("Transform Component"))
							{
								selectedEntity = (*it).first;
								hasTransform = true;
							}
						}

						if (SceneManager::HasLightComponent((*it).first))
						{
							if (ImGui::Button("Light Component"))
							{
								selectedEntity = (*it).first;
								hasLight = true;
							}
						}

						if (SceneManager::HasDirectionalLight((*it).first))
						{
							if (ImGui::Button("Directional Light"))
							{
								selectedEntity = (*it).first;
								//hasDirectional = true;
								hasLight = true;
							}
						}


						if (SceneManager::HasPointLight((*it).first))
						{
							if (ImGui::Button("Point Light"))
							{
								selectedEntity = (*it).first;
								hasLight = true;
							}
						}

						if (SceneManager::HasTestComponent((*it).first))
						{
							if (ImGui::Button("Test Component"))
							{
								selectedEntity = (*it).first;
								hasTest = true;
							}
						}

						if (SceneManager::HasMaterialComponent((*it).first))
						{
							if (ImGui::Button("Material Component"))
							{
								selectedEntity = (*it).first;
								hasMaterial = true;
							}
						}

						ImGui::TreePop();
					}
				}
				ImGui::End();
			}

			//content browser
			{
				ImGui::Begin("Content Browser");

				for (auto& i : std::filesystem::directory_iterator("Assets"))
				{
					if (ImGui::MenuItem(i.path().filename().string().c_str()))
					{
						currentPath = i.path().string();
						openFile = true;
						break;
					}
				}
				if (openFile)
				{
					ImGui::Separator();
					//ImGui::BeginDragDropSource();
					for (auto& p : std::filesystem::directory_iterator(currentPath))
					{
						ImGui::MenuItem(p.path().filename().string().c_str());
						//ImGui::EndDragDropSource();
					}
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

		void Editor::ImGuiInit()
		{
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
			io.ConfigFlags |= ImGuiWindowFlags_Popup;

			ImFont* consola = io.Fonts->AddFontFromFileTTF("Assets/Fonts/CONSOLA.TTF", 14.0f);

			ImGui::StyleColorsDark();
			ImGuiStyle& style = ImGui::GetStyle();

			style.WindowRounding = 0.0f;

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

		void Editor::LoadEntities()
		{
			const char* level = "Levels/demo_level.hclvl";
			HC_CORE_INFO("Loading level: {0}", level);
			LevelManager::OpenLevel(level);
			
			for (auto i : LevelManager::GetNames())
				SceneManager::NewEntity(i);
			//SceneManager::NewComponent(TransformComponent(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), *SceneManager::GetTexture("Default"), glm::vec4(HC_COLOR_WHITE)), SceneManager::GetEntites().size());
			//SceneManager::NewComponent(MaterialComponent(SceneManager::GetTexture("Default")), SceneManager::GetEntites().size());
		}

	private:
		bool holdingRight = false, mouse = false;
		float centerX = 480, centerY = 270;

		//imgui testing
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		//Framebuffer
		Framebuffer framebuffer = Framebuffer(Application::Get().GetWindow());

		float viewportX = 1280, viewportY = 720;

		bool wireframe = false;

		//Entity 0 should not exist
		int selectedEntity = 0;
		bool hasTransform = false;
		bool hasTest = false;
		bool hasLight = false;
		bool hasDirectional = false;
		bool hasPoint = false;
		bool hasMaterial = false;

		bool showStats = false;

		bool openFile = false;
		std::string currentPath = " ";

		char name[32] = "";
	};

	Hercules::Application* Hercules::CreateApplication()
	{
		return new Editor();
	}
}