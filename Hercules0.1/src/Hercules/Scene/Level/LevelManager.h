#pragma once

#include "glm/glm.hpp"
#include "Hercules/Scene/SceneManager.h"

namespace Hercules {
	class LevelManager {
	public:
		LevelManager() {};
		~LevelManager() {};
		
		static const void OpenLevel(const char* levelPath, std::string& projectPath);
		static const void WriteLevel(const char* levelPath, std::string& projectPath);

		static const void NewLevel(std::string levelName);
	};
}