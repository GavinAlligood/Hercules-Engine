#include "imgwh.h"
#include "MenuBar.h"

namespace Hercules {

	void MenuBar::ConditionalRender()
	{
		UIData& r_EditorUIData = UIRenderer::GetEditorUIData();

		//Menu bar
		if (ImGui::BeginMenuBar())
		{
			//print out stats
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New Level"))
				{
					r_EditorUIData.LevelCreationMenuCheck = true;
				}
				ImGui::Separator();

				if (ImGui::MenuItem("Save Level")) LevelManager::WriteLevel(r_EditorUIData.CurrentLevel.c_str(), r_EditorUIData.ProjectPath);
				ImGui::Separator();

				if (ImGui::MenuItem("Open Level"))
				{
					r_EditorUIData.OpenLevelMenuCheck = true;
				}
				ImGui::Separator();

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::Separator();

				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		//Change this to be a FileBrowserPopup type
		if (r_EditorUIData.OpenLevelMenuCheck)
		{
			ImVec2 center = ImGui::GetMainViewport()->GetCenter();
			ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
			ImGui::SetNextWindowSize(ImVec2{ 400,400 });
			ImGui::OpenPopup("Levels");

			if (ImGui::BeginPopupModal("Levels", &r_EditorUIData.OpenLevelMenuCheck, ImGuiWindowFlags_AlwaysAutoResize))
			{
				ImGui::Text("Select level								 ");
				for (auto& i : std::filesystem::directory_iterator(r_EditorUIData.ProjectPath + "Levels"))
				{
					std::string name = i.path().filename().string().substr(0,
						i.path().filename().string().find("."));
					if (ImGui::MenuItem(name.c_str()))
					{
						r_EditorUIData.CurrentLevel = r_EditorUIData.ProjectPath + "Levels/" + name + ".hclvl";
						LevelManager::OpenLevel(r_EditorUIData.CurrentLevel.c_str(), r_EditorUIData.ProjectPath);

						ImGui::CloseCurrentPopup();
						r_EditorUIData.OpenLevelMenuCheck = false;
					}
				}

				ImGui::EndPopup();
			}
		}

		if (r_EditorUIData.LevelCreationMenuCheck)
		{
			ImVec2 center = ImGui::GetMainViewport()->GetCenter();
			ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
			ImGui::OpenPopup("New Level");

			if (ImGui::BeginPopupModal("New Level", NULL, ImGuiWindowFlags_AlwaysAutoResize))
			{
				static char levelname[32] = "";

				ImGui::Text("Enter Level Name: ");
				ImGui::InputText("##levelName", levelname, IM_ARRAYSIZE(levelname));

				ImGui::SameLine();

				if (ImGui::SmallButton("Create"))
				{
					LevelManager::NewLevel(levelname);
					LevelManager::OpenLevel(levelname, r_EditorUIData.ProjectPath);
					r_EditorUIData.CurrentLevel = levelname;
					ImGui::CloseCurrentPopup();
					r_EditorUIData.LevelCreationMenuCheck = false;
				}
				ImGui::SameLine();
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(1.0f, 0.4f, 0.3f));
				if (ImGui::SmallButton("Cancel"))
				{
					r_EditorUIData.LevelCreationMenuCheck = false;
					ImGui::CloseCurrentPopup();
				}
				ImGui::PopStyleColor();
				ImGui::EndPopup();
			}
		}
	}

}