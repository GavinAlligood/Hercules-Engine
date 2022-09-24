#include "../imgwh.h"
#include "MeshMenu.h"

namespace Hercules {

	void MeshMenu::ConditionalRender()
	{
		UIData& r_EditorUIData = UIRenderer::GetEditorUIData();
		int& SelectedEntity = r_EditorUIData.SelectedEntity;

		if (SceneManager::HasMeshComponent(SelectedEntity))
		{
			if (ImGui::CollapsingHeader("Mesh Component"))
			{
				ImGui::Text("Mesh: %s", SceneManager::GetMeshComponent(SelectedEntity)->GetPath().c_str());

				if (ImGui::Button("Open..."))
				{
					ImVec2 center = ImGui::GetMainViewport()->GetCenter();
					ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
					ImGui::OpenPopup("Mesh Select");
				}

				bool p_opened = true;

				if (ImGui::BeginPopupModal("Mesh Select", &p_opened, ImGuiWindowFlags_NoResize)) //AutoResize
				{
					//This will be drag and drop eventually
					//Small browser

					static std::filesystem::path currentPopupPath = r_EditorUIData.ProjectPath + "/Assets/Models";

					if (currentPopupPath != std::filesystem::path(r_EditorUIData.ProjectPath + "/Assets/Models"))
					{
						if (ImGui::Button("<-"))
						{
							currentPopupPath = currentPopupPath.parent_path();
						}
					}

					for (auto& i : std::filesystem::directory_iterator(currentPopupPath))
					{
						std::string name = i.path().filename().string().substr(0,
							i.path().filename().string().find("."));
						if (i.is_directory())
						{
							if (ImGui::Button(name.c_str()))
							{
								currentPopupPath /= i.path().filename();
							}
						}
						else
						{
							std::filesystem::path assets = r_EditorUIData.ProjectPath + "/Assets/Models";
							const auto& path = i.path();
							auto relativePath = std::filesystem::relative(path, assets);
							auto extension = relativePath.extension().string();

							if (extension == ".obj")
							{
								if (ImGui::Button(name.c_str()))
								{
									SceneManager::GetMeshComponent(SelectedEntity)->GetModel().ResetMesh();
									SceneManager::GetMeshComponent(SelectedEntity)->GetModel().loadModel(path.string());
									SceneManager::GetMeshComponent(SelectedEntity)->SetPath(path.string());
									ImGui::CloseCurrentPopup();
								}
							}
						}

					}
					ImGui::EndPopup();
				}

				if (ImGui::Button("Delete"))
				{
					SceneManager::DeleteComponent(ComponentType::Mesh, SelectedEntity);
				}
			}
		}
	}
}