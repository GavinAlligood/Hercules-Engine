#pragma once

#include <iostream>

//#include "Hercules/Renderer/GL/Framebuffer/Framebuffer.h"

namespace Hercules {
	
	struct UIData
	{
		std::string ProjectPath;

		bool QuickMenuCheck = false;
		bool LevelCreationMenuCheck = false;
		
		//its only 3 strings
		std::string EditorLevel = "lvl";
		std::string RuntimeLevel = "lvl";
		std::string CurrentLevel = EditorLevel;
	};
}