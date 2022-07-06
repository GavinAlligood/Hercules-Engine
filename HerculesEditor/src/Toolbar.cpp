#include "imgwh.h"
#include "Toolbar.h"

void Hercules::Toolbar::ConditionalRender()
{
	UIData& r_EditorUIData = UIRenderer::GetEditorUIData();

	ImGui::Begin("Toolbar");

	static float padding = 10;
	static float thumbnailSize = 30;
	float cellSize = thumbnailSize + padding;

	float panelWidth = ImGui::GetContentRegionAvail().x;
	int columnCount = (int)(panelWidth / cellSize);
	if (columnCount < 1) columnCount = 1;

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::Columns(columnCount, 0, false);

	//Save button
	//if (ImGui::ImageButton((ImTextureID)r_EditorUIData.SaveIcon.GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 }))
	//{
	//	LevelManager::WriteLevel(r_EditorUIData.CurrentLevel.c_str(), r_EditorUIData.ProjectPath);
	//}
	//ImGui::NextColumn();

	////Play scene
	////TODO: Disable other buttons (save, etc)
	//if (ImGui::ImageButton((ImTextureID)r_EditorUIData.PlayIcon.GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 }))
	//{
	//	/*
	//	1. Create duplicate scene
	//	2. Run that scene
	//	3. When ending the scene, restore current scene to previous one
	//	*/
	//	LevelManager::WriteLevel(r_EditorUIData.CurrentLevel.c_str(), r_EditorUIData.ProjectPath); //Save the level and the runtime level so that the runtime level is actually up to date
	//	LevelManager::WriteLevel(r_EditorUIData.RuntimeLevel.c_str(), r_EditorUIData.ProjectPath);
	//	r_EditorUIData.CurrentLevel = r_EditorUIData.RuntimeLevel;
	//	r_EditorUIData.RunningInEditorCheck = true;
	//	LevelManager::OpenLevel(r_EditorUIData.CurrentLevel.c_str(), r_EditorUIData.ProjectPath); //runtimeLevel
	//}
	//ImGui::NextColumn();

	//if (r_EditorUIData.RunningInEditorCheck)
	//{
	//	if (ImGui::ImageButton((ImTextureID)r_EditorUIData.StopIcon.GetID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 }))
	//	{
	//		r_EditorUIData.CurrentLevel = r_EditorUIData.EditorLevel;
	//		r_EditorUIData.RunningInEditorCheck = false;
	//		LevelManager::OpenLevel(r_EditorUIData.CurrentLevel.c_str(), r_EditorUIData.ProjectPath); //editorLevel
	//	}
	//}

	ImGui::PopStyleColor();
	ImGui::End();
}
