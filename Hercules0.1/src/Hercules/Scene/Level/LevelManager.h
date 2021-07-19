#pragma once

#include "glm/glm.hpp"
#include "Hercules/Scene/SceneManager.h"

namespace Hercules {
	class LevelManager {
	public:
		LevelManager() {};
		~LevelManager() {};
		
		static const void OpenLevel(const char* levelPath);
		static const void WriteLevel(const char* levelPath);

		static std::vector<std::string> GetNames();
		static std::map<unsigned int, glm::vec3>& GetPositions();
		static std::map<unsigned int, glm::vec3>& GetScales();
		static std::map<unsigned int, glm::vec3>& GetRotations();

		static glm::vec3* GetPosition(unsigned int id);
		static glm::vec3* GetScale(unsigned int id);
		static glm::vec3* GetRotation(unsigned int id);
	};

	struct LevelData {
		//only used when loading a scene or saving so its fine
		std::vector<std::string> names;
		std::map<unsigned int, glm::vec3> positions;
		std::map<unsigned int, glm::vec3> scales;
		std::map<unsigned int, glm::vec3> rotations;
	};
}