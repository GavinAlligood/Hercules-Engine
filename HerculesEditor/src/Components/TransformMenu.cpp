#include "../imgwh.h"
#include "TransformMenu.h"

namespace Hercules {
	
	void TransformMenu::ConditionalRender()
	{
		UIData& r_EditorUIData = UIRenderer::GetEditorUIData();
		int& SelectedEntity = r_EditorUIData.SelectedEntity;
		
		//TODO: Double check this line is necessary
		if (SceneManager::HasTransformComponent(SelectedEntity))
		{
			if (ImGui::CollapsingHeader("Transform Component"))
			{
				float xPos = SceneManager::GetTransformComponent(SelectedEntity)->GetPos().x;
				float yPos = SceneManager::GetTransformComponent(SelectedEntity)->GetPos().y;
				float zPos = SceneManager::GetTransformComponent(SelectedEntity)->GetPos().z;

				ImGui::Text("Position");
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(1.0f, 0.4f, 0.3f));
				ImGui::Button("X"); ImGui::SameLine();
				ImGui::DragFloat("##Xpos", &xPos, 0.1f, 0.0f, 0.0f, "%.2f");
				ImGui::PopStyleColor();

				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0.7f, 1.0f, 0.4f));
				ImGui::Button("Y"); ImGui::SameLine();
				ImGui::DragFloat("##Ypos", &yPos, 0.1f, 0.0f, 0.0f, "%.2f");
				ImGui::PopStyleColor();

				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0.4f, 0.7f, 1.0f));
				ImGui::Button("Z"); ImGui::SameLine();
				ImGui::DragFloat("##Zpos", &zPos, 0.1f, 0.0f, 0.0f, "%.2f");
				ImGui::PopStyleColor();

				float xScale = SceneManager::GetTransformComponent(SelectedEntity)->GetScale().x;
				float yScale = SceneManager::GetTransformComponent(SelectedEntity)->GetScale().y;
				float zScale = SceneManager::GetTransformComponent(SelectedEntity)->GetScale().z;

				ImGui::Text("Scale");
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(1.0f, 0.4f, 0.3f));
				ImGui::Button("X"); ImGui::SameLine();
				ImGui::DragFloat("##Xwidth", &xScale, 0.1f, 0.0f, 0.0f, "%.2f");
				ImGui::PopStyleColor();

				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0.7f, 1.0f, 0.4f));
				ImGui::Button("Y"); ImGui::SameLine();
				ImGui::DragFloat("##Ywidth", &yScale, 0.1f, 0.0f, 0.0f, "%.2f");
				ImGui::PopStyleColor();

				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0.4f, 0.7f, 1.0f));
				ImGui::Button("Z"); ImGui::SameLine();
				ImGui::DragFloat("##Zwidth", &zScale, 0.1f, 0.0f, 0.0f, "%.2f");
				ImGui::PopStyleColor();

				float xRot = SceneManager::GetTransformComponent(SelectedEntity)->GetRotation().x;
				float yRot = SceneManager::GetTransformComponent(SelectedEntity)->GetRotation().y;
				float zRot = SceneManager::GetTransformComponent(SelectedEntity)->GetRotation().z;

				ImGui::Text("Rotation");
				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(1.0f, 0.4f, 0.3f));
				ImGui::Button("X"); ImGui::SameLine();
				ImGui::DragFloat("##Xrot", &xRot, 0.1f, 0.0f, 0.0f, "%.2f");
				ImGui::PopStyleColor();

				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0.7f, 1.0f, 0.4f));
				ImGui::Button("Y"); ImGui::SameLine();
				ImGui::DragFloat("##Yrot", &yRot, 0.1f, 0.0f, 0.0f, "%.2f");
				ImGui::PopStyleColor();

				ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0.4f, 0.7f, 1.0f));
				ImGui::Button("Z"); ImGui::SameLine();
				ImGui::DragFloat("##Zrot", &zRot, 0.1f, 0.0f, 0.0f, "%.2f");
				ImGui::PopStyleColor();

				SceneManager::GetTransformComponent(SelectedEntity)->SetPos(glm::vec3(xPos, yPos, zPos));
				SceneManager::GetTransformComponent(SelectedEntity)->SetScale(glm::vec3(xScale, yScale, zScale));
				SceneManager::GetTransformComponent(SelectedEntity)->SetRotation(glm::vec3(xRot, yRot, zRot));
			}
		}
	}
}