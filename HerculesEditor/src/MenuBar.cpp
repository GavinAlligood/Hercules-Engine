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
	}

}