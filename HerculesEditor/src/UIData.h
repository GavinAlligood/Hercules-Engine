#pragma once

#include <iostream>

namespace Hercules {

	struct UIData
	{
		bool QuickMenuCheck = false;
		bool LevelCreationMenuCheck = false;
		bool OpenLevelMenuCheck = false;
		bool StatsMenuCheck = false;

		bool RunningInEditorCheck = false;

		int SelectedEntity = 0;

		bool wireframe = false;

		//Note that these variables are temporary!
		//TODO: Change this when working on project system
		std::string ProjectPath;
		std::string EditorLevel = ProjectPath + "Levels/demo_level.hclvl";
		std::string RuntimeLevel = ProjectPath + "Runtime/demo_level.hcrt";
		std::string CurrentLevel = EditorLevel;

		glm::vec2 m_ViewportSize = glm::vec2(0.0f);
		glm::vec2 m_ViewportBounds[2];
	};	
}