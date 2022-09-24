#include "../imgwh.h"
#include "MaterialMenu.h"

namespace Hercules {
	
	void MaterialMenu::ConditionalRender()
	{
		UIData& r_EditorUIData = UIRenderer::GetEditorUIData();
		int& SelectedEntity = r_EditorUIData.SelectedEntity;

		if (SceneManager::HasMeshComponent(SelectedEntity))
		{
			if (ImGui::CollapsingHeader("Material"))
			{
				/*ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
				color.x = SceneManager::GetMeshComponent(SelectedEntity)->GetColor().x;
				color.y = SceneManager::GetMeshComponent(SelectedEntity)->GetColor().y;
				color.z = SceneManager::GetMeshComponent(SelectedEntity)->GetColor().z;*/

				//float shininess = SceneManager::GetMeshComponent(SelectedEntity)->GetShininess();

				//ImGui::ColorPicker3("Select Material", (float*)&color);

				//ImGui::DragFloat("Shininess", &shininess, 0.1f, 2.0f, 256.0f, "%.2f");

				//SceneManager::GetMeshComponent(SelectedEntity)->SetShininess(shininess);
				//SceneManager::GetMeshComponent(SelectedEntity)->SetColor(glm::vec3(color.x, color.y, color.z));

				if (ImGui::SmallButton("Material"))
				{
					ImVec2 center = ImGui::GetMainViewport()->GetCenter();
					ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
					//ImGui::OpenPopup("Select Material");
					ImGui::OpenPopup("Material Select");
				}

				bool p_opened = true;

				//TODO: Update this UI, and change this option to select a material no matter where it is placed
				if (ImGui::BeginPopupModal("Material Select", &p_opened, ImGuiWindowFlags_NoResize))
				{
					for (auto& i : std::filesystem::directory_iterator(r_EditorUIData.ProjectPath + "/Assets/Materials"))
					{
						std::string name = i.path().filename().string().substr(0,
							i.path().filename().string().find("."));

						std::filesystem::path assets = r_EditorUIData.ProjectPath + "/Assets/Materials";
						const auto& path = i.path();
						auto relativePath = std::filesystem::relative(path, assets);
						auto extension = relativePath.extension().string();
						if (extension == ".hcmat")
						{
							if (ImGui::Button(name.c_str()))
							{
								auto m = SceneManager::GetMeshComponent(SelectedEntity);
								SceneManager::GetMeshComponent(SelectedEntity);
								//m->SetColor(*LevelManager::GetColor(name));
								//m->SetShininess(*LevelManager::GetShininess(name));
								//m->SetName(name);
								ImGui::CloseCurrentPopup();
							}
						}
					}

					ImGui::EndPopup();
				}

				ImGui::SameLine();
				ImGui::Image((void*)SceneManager::GetMeshComponent(SelectedEntity)->GetTexture()->GetID(), ImVec2{ 50, 50 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
			}
		}
	}
}