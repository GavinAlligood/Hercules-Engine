#include "imgwh.h"
#include "StatsMenu.h"

namespace Hercules {

	void StatsMenu::ConditionalRender()
	{
		UIData& r_EditorUIData = UIRenderer::GetEditorUIData();
		
		if (r_EditorUIData.StatsMenuCheck)
		{
			ImGui::SetNextWindowBgAlpha(0.35f);

			ImGui::Begin("Performance", &r_EditorUIData.StatsMenuCheck, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);

			ImGui::Text("Level: %s", r_EditorUIData.CurrentLevel.c_str());
			ImGui::Text("FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::Text("Entities: %.1i", SceneManager::GetEntites().size());
			ImGui::Text("Test Components: %.1i", SceneManager::GetDemoComponentList().size());
			ImGui::Text("Mesh Components: %.1i", SceneManager::GetMeshComponentList().size());
			ImGui::Text("Transform Components: %.1i", SceneManager::GetTransformComponentList().size());
			ImGui::Text("Directional Lights: %.1i", SceneManager::GetDirectionalLightList().size());
			ImGui::Text("Point Lights: %.1i", SceneManager::GetPointLightList().size());
			ImGui::Text("Spot Lights: %.1i", SceneManager::GetSpotLightList().size());
			ImGui::Text("Textures: %.1i", SceneManager::GetTextureList().size());
			ImGui::Text("Material Components: %.1i", SceneManager::GetMaterialComponentList().size());
			ImGui::End();
		}
	}

}