#include "imgwh.h"
#include "SceneHeirarchy.h"

namespace Hercules {
	void SceneHeirarchy::ConditionalRender()
	{
		UIData& r_EditorUIData = UIRenderer::GetEditorUIData();

		ImGui::Begin("Scene Components");

		if (ImGui::SmallButton("New Entity")) { ImGui::OpenPopup("New Entity"); }
		ImGui::SameLine();
		if (ImGui::SmallButton("Clear")) { r_EditorUIData.SelectedEntity = 0; }

		ImGui::Separator();

		//Create a heirarchy of buttons corresponding to entities
		std::map<unsigned int, std::string>::iterator it;
		for (it = SceneManager::GetEntities().begin();
			it != SceneManager::GetEntities().end(); ++it)
		{
			if (ImGui::SmallButton((*it).second.c_str()))
			{
				r_EditorUIData.SelectedEntity = (*it).first;
			}
		}

		//New Entity Popup
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
				unsigned int size = SceneManager::GetEntities().size();
				//SceneManager::NewComponent(MeshComponent(r_EditorUIData.ProjectPath + "/Assets/Models/Cube3/cube.obj"), size);
				SceneManager::NewComponent(TransformComponent(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f)), size);
				//SceneManager::NewComponent(MaterialComponent(SceneManager::GetTexture("Plastic"), *LevelManager::GetColor("Plastic")), size);
				//SceneManager::GetMaterialComponent(SceneManager::GetEntites().size())->SetName("Plastic"); //wait why am i doing this?
				HC_INFO("Created new entity: {0}", name);
				memset(name, 0, sizeof(name)); // Reset name
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			ImGui::EndPopup();
		}

		ImGui::End();
	}
}