#pragma once

#include <iostream>

//#include "Hercules/Renderer/GL/Framebuffer/Framebuffer.h"

namespace Hercules {
	
	//extern Framebuffer m_Framebuffer;

	struct UIData
	{
		std::string ProjectPath;

		bool QuickMenuCheck = false;
		bool LevelCreationMenuCheck = false;
		bool OpenLevelMenuCheck = false;
		bool StatsMenuCheck = false;
		bool LightComponentMenuCheck = false;
		bool TestComponentMenuCheck = false;
		bool TransformComponentMenuCheck = false;
		bool MeshComponentMenuCheck = false;
		bool MaterialComponentMenuCheck = false;

		bool RunningInEditorCheck = false;

		int SelectedEntity = 0;

		//These could potentially be moved here and I will delete UIRenderer's SetLevels function
		std::string EditorLevel = "lvl";
		std::string RuntimeLevel = "lvl";
		std::string CurrentLevel = EditorLevel;

		//Icons
		//Texture FolderIcon = Texture("Resources/Icons/folder.png", 1, true);
		//Texture FileIcon = Texture("Resources/Icons/document.png", 1, true);
		//Texture ImageIcon = Texture("Resources/Icons/picture.png", 1, true);
		//Texture FontIcon = Texture("Resources/Icons/font.png", 1, true);
		//Texture MatIcon = Texture("Resources/Icons/sphere.png", 1, true);
		//Texture ShaderIcon = Texture("Resources/Icons/shader.png", 1, true);
		//Texture ModelIcon = Texture("Resources/Icons/model.png", 1, true);
		//Texture UnknownIcon = Texture("Resources/Icons/unknown.png", 1, true);
		//Texture SaveIcon = Texture("Resources/Icons/disk.png", 1, true);
		//Texture PlayIcon = Texture("Resources/Icons/play_button.png", 1, true);
		//Texture StopIcon = Texture("Resources/Icons/stop.png", 1, true);

		glm::vec2 m_ViewportSize = glm::vec2(0.0f);
		//Called in update
		//glm::vec2 m_ViewportBounds[2];

		//Need to include framebuffer here
		//Framebuffer m_Framebuffer = Framebuffer(Application::Get().GetWindow().GetWidth(),
			//Application::Get().GetWindow().GetHeight());
	};	
}