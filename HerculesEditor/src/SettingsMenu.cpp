#include "imgwh.h"
#include "SettingsMenu.h"

namespace Hercules {

	void SettingsMenu::ConditionalRender()
	{
		UIData& r_EditorUIData = UIRenderer::GetEditorUIData();

		ImGui::Begin("Settings");
		
		if (ImGui::Checkbox("Wireframe", &r_EditorUIData.wireframe))
		{
			if (r_EditorUIData.wireframe) { HC_VIEW_WIREFRAME; HC_STAT("Wireframe enabled"); }
			else { HC_VIEW_NORMAL; HC_STAT("Wireframe disabled"); }
		}
		ImGui::Checkbox("Show Performance Overlay", &r_EditorUIData.StatsMenuCheck);

		ImGui::Separator();
		ImVec4 bgColor = ImVec4(SceneManager::GetBackgroundColor().x,
			SceneManager::GetBackgroundColor().y, SceneManager::GetBackgroundColor().z, 1.0f);

		//TODO: Save this data to scene's file
		//ImGui::ColorPicker3("Light Color", (float*)&color);
		ImGui::ColorPicker3("Background Color", (float*)&bgColor);
		SceneManager::SetBackgroundColor(bgColor.x, bgColor.y, bgColor.z);

		static int style_idx = -1;
		if (ImGui::Combo("Theme", &style_idx, "Light (banana)\0Dark"))
		{
			switch (style_idx)
			{
			case 0: UseStyleLightMode(); break;
			case 1: UseStyleDarkMode(); break;
			}
		}

		ImGui::End();
	}

	void SettingsMenu::UseStyleDarkMode()
	{
		ImVec4* colors = ImGui::GetStyle().Colors;

		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.32f, 0.32f, 0.32f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.16f, 0.16f, 0.16f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.50f, 0.50f, 0.50f, 0.50f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.98f, 0.98f, 0.98f, 0.40f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.26f, 0.26f, 1.00f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.23f, 0.23f, 0.23f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.32f, 0.32f, 0.32f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.37f, 0.37f, 0.37f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.11f, 0.11f, 0.11f, 0.71f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.81f, 0.81f, 0.81f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_Button] = ImVec4(0.46f, 0.46f, 0.46f, 0.40f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.72f, 0.72f, 0.72f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_Header] = ImVec4(0.45f, 0.45f, 0.45f, 0.40f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.72f, 0.72f, 0.72f, 1.00f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
		colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.40f, 0.50f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.73f, 0.73f, 0.73f, 0.78f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.62f, 0.62f, 0.62f, 0.25f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.82f, 0.82f, 0.82f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.95f);
		colors[ImGuiCol_Tab] = ImVec4(0.30f, 0.30f, 0.30f, 0.86f);
		colors[ImGuiCol_TabHovered] = ImVec4(0.72f, 0.72f, 0.72f, 1.00f);
		colors[ImGuiCol_TabActive] = ImVec4(0.58f, 0.58f, 0.58f, 1.00f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.24f, 0.24f, 0.24f, 0.97f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_DockingPreview] = ImVec4(0.88f, 0.88f, 0.88f, 0.70f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.93f, 0.93f, 0.93f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.93f, 0.93f, 0.93f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	}

	void SettingsMenu::UseStyleLightMode()
	{
		ImVec4* colors = ImGui::GetStyle().Colors;

		colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.98f);
		colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
		colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.838f, 0.838f, 0.838f, 1.000f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.791f, 0.791f, 0.791f, 1.000f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.597f, 0.597f, 0.597f, 1.000f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
		colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 0.877f, 0.557f, 1.000f);
		colors[ImGuiCol_SliderGrab] = ImVec4(1.000f, 0.933f, 0.557f, 1.000f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(1.000f, 0.863f, 0.557f, 1.000f);
		colors[ImGuiCol_Button] = ImVec4(0.717f, 0.717f, 0.717f, 0.400f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.859f, 0.835f, 0.472f, 1.000f);
		colors[ImGuiCol_Header] = ImVec4(0.718f, 0.718f, 0.718f, 0.400f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.853f, 0.829f, 0.465f, 1.000f);
		colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.864f, 0.840f, 0.479f, 1.000f);
		colors[ImGuiCol_Tab] = ImVec4(0.718f, 0.718f, 0.718f, 0.400f);
		colors[ImGuiCol_TabHovered] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
		colors[ImGuiCol_TabActive] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.792f, 0.792f, 0.792f, 1.000f);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.941f, 0.941f, 0.941f, 1.000f);
		colors[ImGuiCol_DockingPreview] = ImVec4(1.000f, 0.973f, 0.557f, 0.780f);
		colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.775f, 0.775f, 0.775f, 1.000f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.000f, 0.973f, 0.557f, 1.000f);
		colors[ImGuiCol_NavHighlight] = colors[ImGuiCol_HeaderHovered];
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
	}

}