#include "imgwh.h"
#include "SceneHeirarchy.h"

namespace Hercules {
	void SceneHeirarchy::ConditionalRender()
	{
		UIData& r_EditorUIData = UIRenderer::GetEditorUIData();

		ImGui::Begin("Scene Components");

		if (ImGui::MenuItem("New Entity"))
		{
			ImGui::OpenPopup("New Entity");
		}

		ImVec2 center = ImGui::GetMainViewport()->GetCenter();
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

		bool p_opened = true;

		if (ImGui::BeginPopupModal("New Entity", &p_opened, ImGuiWindowFlags_AlwaysAutoResize))
		{
			char name[32] = "";

			ImGui::Text("Enter Entity Name: ");
			ImGui::InputText("##Name", name, IM_ARRAYSIZE(name));

			ImGui::SameLine();

			//TODO: Make a check to ensure there aren't duplicate entity names
			if (ImGui::SmallButton("Create"))
			{
				SceneManager::NewEntity((std::string)name);
				//Automatic components entities have by default
				unsigned int size = SceneManager::GetEntites().size();
				SceneManager::NewComponent(MeshComponent(r_EditorUIData.ProjectPath + "/Assets/Models/Cube3/cube.obj"), size);
				SceneManager::NewComponent(TransformComponent(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f)), size);
				SceneManager::NewComponent(MaterialComponent(SceneManager::GetTexture("Plastic"), *LevelManager::GetColor("Plastic")), size);
				SceneManager::GetMaterialComponent(SceneManager::GetEntites().size())->SetName("Plastic"); //wait why am i doing this?
				HC_INFO("Created new entity: {0}", name);
				memset(name, 0, sizeof(name)); // Reset name
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			ImGui::EndPopup();
		}

		std::map<unsigned int, std::string>::iterator it;
		for (it = SceneManager::GetEntites().begin();
			it != SceneManager::GetEntites().end(); ++it)
		{
			//icon
			if (ImGui::TreeNode((void*)(intptr_t)(*it).first, "%s", (*it).second.c_str()))
			{
				//Might end up changing slightly in future
				ImGui::SameLine();

				if (ImGui::SmallButton("Edit"))
				{
					r_EditorUIData.SelectedEntity = (*it).first;
				}

				if (SceneManager::HasTransformComponent((*it).first))
				{
					if (ImGui::Button("Transform Component"))
					{
						r_EditorUIData.SelectedEntity = (*it).first;
						r_EditorUIData.TransformComponentMenuCheck = true;
					}
				}

				if (SceneManager::HasLightComponent((*it).first))
				{
					if (ImGui::Button("Light Component"))
					{
						r_EditorUIData.SelectedEntity = (*it).first;
						r_EditorUIData.LightComponentMenuCheck = true;
					}
				}

				if (SceneManager::HasDirectionalLight((*it).first))
				{
					if (ImGui::Button("Directional Light"))
					{
						r_EditorUIData.SelectedEntity = (*it).first;
						r_EditorUIData.LightComponentMenuCheck = true;
					}
				}


				if (SceneManager::HasPointLight((*it).first))
				{
					if (ImGui::Button("Point Light"))
					{
						r_EditorUIData.SelectedEntity = (*it).first;
						r_EditorUIData.LightComponentMenuCheck = true;
					}
				}

				if (SceneManager::HasTestComponent((*it).first))
				{
					if (ImGui::Button("Test Component"))
					{
						r_EditorUIData.SelectedEntity = (*it).first;
						r_EditorUIData.TestComponentMenuCheck = true;
					}
				}

				if (SceneManager::HasMaterialComponent((*it).first))
				{
					if (ImGui::Button("Material Component"))
					{
						r_EditorUIData.SelectedEntity = (*it).first;
						r_EditorUIData.MaterialComponentMenuCheck = true;
					}
				}

				if (SceneManager::HasMeshComponent((*it).first))
				{
					if (ImGui::Button("Mesh Component"))
					{
						r_EditorUIData.SelectedEntity = (*it).first;
						r_EditorUIData.MeshComponentMenuCheck = true;
					}
				}

				ImGui::TreePop();
			}
		}
		ImGui::End();
	}
}