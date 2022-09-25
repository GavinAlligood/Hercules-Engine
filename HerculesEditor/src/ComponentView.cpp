#include "imgwh.h"
#include "ComponentView.h"

namespace Hercules {
	
	void ComponentView::ConditionalRender()
	{
		UIData& r_EditorUIData = UIRenderer::GetEditorUIData();

		ImGui::Begin("Component View");

		if (r_EditorUIData.SelectedEntity != 0)
		{
			ImGui::Text("Entity ID: %i", r_EditorUIData.SelectedEntity);

			//ImGui::SameLine();

			if (ImGui::SmallButton("Add.."))
			{
				//SceneManager::NewComponent()
				ImGui::OpenPopup("new-component");
			}

			if (ImGui::BeginPopup("new-component"))
			{
				ImGui::Text("Create Component");
				if (ImGui::SmallButton("Directional Light"))
				{
					if (!SceneManager::HasLightComponent(r_EditorUIData.SelectedEntity))
						SceneManager::NewComponent(DirectionalLight(), r_EditorUIData.SelectedEntity);
				}
				if (ImGui::SmallButton("Point Light"))
				{
					if (!SceneManager::HasLightComponent(r_EditorUIData.SelectedEntity))
						SceneManager::NewComponent(PointLight(), r_EditorUIData.SelectedEntity);
				}
				if (ImGui::SmallButton("Mesh Component"))
				{
					if (!SceneManager::HasMeshComponent(r_EditorUIData.SelectedEntity))
					{
						if (!SceneManager::HasMeshComponent(r_EditorUIData.SelectedEntity))
						{
							SceneManager::NewComponent(MeshComponent("Plastic", SceneManager::GetTexture("Plastic")), r_EditorUIData.SelectedEntity);
						}
						SceneManager::NewComponent(MeshComponent(r_EditorUIData.ProjectPath + "/Assets/Models/Cube3/cube.obj"), r_EditorUIData.SelectedEntity);
					}
				}

				ImGui::EndPopup();
			}

			ImGui::SameLine();

			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(1.0f, 0.4f, 0.3f));
			if (ImGui::SmallButton("Delete"))
			{
				if (SceneManager::HasTransformComponent(r_EditorUIData.SelectedEntity)) { SceneManager::DeleteComponent(ComponentType::Transform, r_EditorUIData.SelectedEntity); }
				//if (SceneManager::HasMaterialComponent(r_EditorUIData.SelectedEntity)) { SceneManager::DeleteComponent(ComponentType::Material, r_EditorUIData.SelectedEntity); }
				if (SceneManager::HasDirectionalLight(r_EditorUIData.SelectedEntity)) { SceneManager::DeleteComponent(ComponentType::DirectionalLight, r_EditorUIData.SelectedEntity); }
				if (SceneManager::HasPointLight(r_EditorUIData.SelectedEntity)) { SceneManager::DeleteComponent(ComponentType::PointLight, r_EditorUIData.SelectedEntity); }
				if (SceneManager::HasSpotLight(r_EditorUIData.SelectedEntity)) { SceneManager::DeleteComponent(ComponentType::SpotLight, r_EditorUIData.SelectedEntity); }
				//might need to move this
				if (SceneManager::HasMeshComponent(r_EditorUIData.SelectedEntity)) { SceneManager::DeleteComponent(ComponentType::Mesh, r_EditorUIData.SelectedEntity); }

				SceneManager::DeleteEntity(r_EditorUIData.SelectedEntity);

				//Reset entity ID's above the deleted Entity 

				for (auto& i : SceneManager::GetEntities())
				{
					if (i.first > r_EditorUIData.SelectedEntity)
					{
						auto id = SceneManager::GetEntities().extract(i.first);
						id.key() = i.first - 1;
						SceneManager::GetEntities().insert(std::move(id));
					}
				}

				for (auto& i : SceneManager::GetTransformComponentList())
				{
					if (i.first > r_EditorUIData.SelectedEntity)
					{
						auto id = SceneManager::GetTransformComponentList().extract(i.first);
						id.key() = i.first - 1;
						SceneManager::GetTransformComponentList().insert(std::move(id));
					}
				}

				for (auto& i : SceneManager::GetDirectionalLightList())
				{
					if (i.first > r_EditorUIData.SelectedEntity)
					{
						auto id = SceneManager::GetDirectionalLightList().extract(i.first);
						id.key() = i.first - 1;
						SceneManager::GetDirectionalLightList().insert(std::move(id));
					}
				}

				for (auto& i : SceneManager::GetMeshComponentList())
				{
					if (i.first > r_EditorUIData.SelectedEntity)
					{
						auto id = SceneManager::GetMeshComponentList().extract(i.first);
						id.key() = i.first - 1;
						SceneManager::GetMeshComponentList().insert(std::move(id));
					}
				}

				//TODO: Spot light

				//TODO: Point light

				/*for (auto& i : SceneManager::GetEntites())
				{
					HC_CORE_TRACE(i.first);
				}*/

				r_EditorUIData.SelectedEntity = 0;
			}
			ImGui::PopStyleColor();
		}

		//Component Menus
		TransformMenu::ConditionalRender();
		MaterialMenu::ConditionalRender();
		MeshMenu::ConditionalRender();
		LightMenu::ConditionalRender();
		
		//Put new components here

		ImGui::End();
	}
}