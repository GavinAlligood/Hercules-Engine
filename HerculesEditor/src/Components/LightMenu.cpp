#include "../imgwh.h"
#include "LightMenu.h"

namespace Hercules {
	
	void LightMenu::ConditionalRender()
	{
		UIData& r_EditorUIData = UIRenderer::GetEditorUIData();
		int& SelectedEntity = r_EditorUIData.SelectedEntity;

		if (SceneManager::HasDirectionalLight(SelectedEntity))
		{
			if (ImGui::CollapsingHeader("Light Component"))
			{
				//seperator
				ImGui::Text("Light Component");

				ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
				color.x = SceneManager::GetDirectionalLightComponent(SelectedEntity)->GetColor().x;
				color.y = SceneManager::GetDirectionalLightComponent(SelectedEntity)->GetColor().y;
				color.z = SceneManager::GetDirectionalLightComponent(SelectedEntity)->GetColor().z;
				float ambient = SceneManager::GetDirectionalLightComponent(SelectedEntity)->GetAmbient();

				ImGui::ColorPicker3("Light Color", (float*)&color);
				ImGui::DragFloat("Ambient", &ambient, 0.1f, 0.0f, 0.0f, "%.2f");

				SceneManager::GetDirectionalLightComponent(SelectedEntity)->SetColor(glm::vec3(color.x, color.y, color.z));
				SceneManager::GetDirectionalLightComponent(SelectedEntity)->SetAmbient(ambient);

				if (ImGui::SmallButton("Delete"))
				{
					SceneManager::DeleteComponent(ComponentType::Light, SelectedEntity);
				}
			}
		}
	}
}