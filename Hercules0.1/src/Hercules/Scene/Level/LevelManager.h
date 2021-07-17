#pragma once

#include "glm/glm.hpp"

namespace Hercules {
	class LevelManager {
	public:
		LevelManager() {};
		~LevelManager() {};
		
		static const void OpenLevel(const char* levelPath);

		static const std::vector<std::string> GetNames();

	private:

	};

	struct LevelData {
		//only used when loading a scene or saving so its fine
		std::vector<std::string> names;
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> scales;
		std::vector<glm::vec3> rotations;
	};
}