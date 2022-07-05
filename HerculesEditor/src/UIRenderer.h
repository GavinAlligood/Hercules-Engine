#pragma once

#include "FileBrowser.h"

#include "Hercules/Application/Application.h"
#include "Hercules/Core/Log/Log.h"
#include "Hercules/Core/Input/Input.h"
#include "Hercules/Scene/Level/LevelManager.h"

#include "UIData.h"

#include "QuickMenu.h"
#include "MenuBar.h"

namespace Hercules {
	class UIRenderer {
	public:
		UIRenderer();
		~UIRenderer();

		void Init();

		void NewFrame();
		void Render();

		void SetLevels(std::string editorLevel, std::string runtimeLevel, std::string currentLevel);

		static UIData& GetEditorUIData();

		inline Framebuffer& GetFramebuffer() { return m_Framebuffer; }
	private:
		Framebuffer m_Framebuffer = Framebuffer(Application::Get().GetWindow().GetWidth(),
			Application::Get().GetWindow().GetHeight());
	};
}