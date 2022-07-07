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

		static void ProcessMaterials(const char* levelPath);

		static glm::vec3* GetColor(std::string name);
		static float* GetShininess(std::string name);
	};

	struct LevelData {
		std::map<std::string, glm::vec3> matColors;
		std::map<std::string, float> matShinies;
	};
}