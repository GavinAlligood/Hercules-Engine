#pragma once
#include <Hercules.h>
#include "UIRenderer.h"

#include "imgui_internal.h"

#define IMGUI_DEFINE_MATH_OPERATORS

namespace Hercules {

	class Editor : public Hercules::Application
	{
	public:
		Editor(const char* name, std::string projectPath, bool isGame);

		~Editor();

		//need work
		void Input();

		void Editor::Start() override;

		void Editor::Update() override;

		void OnEvent(Event& e) override;

		void Editor::UpdateFramebuffer();

		void Editor::ImGuiRender();

		//void Editor::ImGuiInit();

		/*void Editor::UseStyleLightMode();

		void Editor::UseStyleDarkMode();*/

	private:
		//should probably prepend "m_" to these
		bool holdingRight = false;
		bool holdingMiddle = false;
		bool inEditor = false;
		float backupX = 0; float backupY = 0;
		bool firstPan = true;
		//bool quickMenu = false;

		bool runningInEditor = false;

		//imgui testing
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		//Framebuffer
		/*Framebuffer m_Framebuffer = Framebuffer(Application::Get().GetWindow().GetWidth(),
			Application::Get().GetWindow().GetHeight());*/
		Framebuffer m_Framebuffer;


		glm::vec2 m_ViewportSize = glm::vec2(0.0f);
		glm::vec2 m_ViewportBounds[2];

		/*Texture folderIcon = Texture("Resources/Icons/folder.png", 1, true);
		Texture fileIcon = Texture("Resources/Icons/document.png", 1, true);
		Texture imageIcon = Texture("Resources/Icons/picture.png", 1, true);
		Texture fontIcon = Texture("Resources/Icons/font.png", 1, true);
		Texture matIcon = Texture("Resources/Icons/sphere.png", 1, true);
		Texture shaderIcon = Texture("Resources/Icons/shader.png", 1, true);
		Texture modelIcon = Texture("Resources/Icons/model.png", 1, true);
		Texture unknownIcon = Texture("Resources/Icons/unknown.png", 1, true);
		Texture saveIcon = Texture("Resources/Icons/disk.png", 1, true);
		Texture playIcon = Texture("Resources/Icons/play_button.png", 1, true);
		Texture stopIcon = Texture("Resources/Icons/stop.png", 1, true);*/

		bool wireframe = false;

		//Entity 0 should not exist
		int selectedEntity = 0;
		bool hasTransform = false;
		bool hasTest = false;
		bool hasLight = false;
		bool hasDirectional = false;
		bool hasPoint = false;
		bool hasMaterial = false;
		bool hasMesh = false;

		bool showStats = false;

		char name[32] = "";
		bool level = false;
		bool newLevel = false;
		std::string m_ProjectPath = "";
		//runtime needs to change
		std::string m_EditorLevel = m_ProjectPath + "Levels/demo_level.hclvl";
		std::string m_RuntimeLevel = m_ProjectPath + "Runtime/demo_level.hcrt";
		std::string m_CurrentLevel = m_EditorLevel;

		bool openFile = false;
		std::filesystem::path currentPath = m_ProjectPath + "/Assets";

		UIRenderer EditorUIRenderer = UIRenderer();
	};
}