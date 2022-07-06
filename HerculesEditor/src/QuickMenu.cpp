#include "imgwh.h"
#include "QuickMenu.h"

#include <iostream>

namespace Hercules {

	void QuickMenu::ConditionalRender()
	{
		UIData& r_EditorUIData = UIRenderer::GetEditorUIData();
		
		if (r_EditorUIData.QuickMenuCheck)
			ImGui::OpenPopup("quick-menu");

		if (ImGui::BeginPopup("quick-menu"))
		{
			//should this be else-if?
			//NOTE: Have section to add new stuff to the scene,
			//and have a section to add stuff to project
			ImGui::Text("New...");
			ImGui::Separator();
			if (ImGui::MenuItem("Empty Entity"))
			{
				std::string name = "Entity" + std::to_string(SceneManager::GetEntites().size() + 1);
				SceneManager::NewEntity(name);
				SceneManager::NewComponent(TransformComponent(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f)), SceneManager::GetEntites().size());
			}
			if (ImGui::MenuItem("Cube"))
			{
				std::string name = "Cube" + std::to_string(SceneManager::GetEntites().size() + 1);
				SceneManager::NewEntity(name);
				unsigned int size = SceneManager::GetEntites().size();
				SceneManager::NewComponent(MeshComponent(r_EditorUIData.ProjectPath + "/Assets/Models/Cube3/cube.obj"), size);
				SceneManager::NewComponent(TransformComponent(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f)), size);
				SceneManager::NewComponent(MaterialComponent(SceneManager::GetTexture("Plastic"), *LevelManager::GetColor("Plastic")), size);
				SceneManager::GetMaterialComponent(SceneManager::GetEntites().size())->SetName("Plastic"); //i think this is neccesary so that the material in the game's save file isn't blank
			}
			if (ImGui::MenuItem("Light"))
			{
				std::string name = "Light" + SceneManager::GetEntites().size();
				SceneManager::NewEntity(name);
				SceneManager::NewComponent(TransformComponent(glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f)), SceneManager::GetEntites().size());
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Material"))
			{

			}

			ImGui::EndPopup();
		}
	}

}