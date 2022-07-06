#pragma once

#include "FileBrowser.h"

#include "Hercules/Application/Application.h"
#include "Hercules/Core/Log/Log.h"
#include "Hercules/Core/Input/Input.h"
#include "Hercules/Scene/Level/LevelManager.h"

#include "UIData.h"

#include "QuickMenu.h"
#include "MenuBar.h"
#include "SettingsMenu.h"
#include "StatsMenu.h"
#include "ComponentView.h"
#include "Toolbar.h"
#include "Viewport.h"

namespace Hercules {
	class UIRenderer {
	public:
		UIRenderer();
		~UIRenderer();

		static void Init();
		
		static void NewFrame();
		static void Render();

		static void SetLevels(std::string editorLevel, std::string runtimeLevel, std::string currentLevel);
		static void CreateIcons();

		static UIData& GetEditorUIData();
	};
}