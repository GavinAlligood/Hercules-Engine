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

		static void LoadMaterials();

		static std::vector<std::string> GetNames();
		static std::vector<std::string> GetMaterialNames();
		static std::map<unsigned int, glm::vec3>& GetPositions();
		static std::map<unsigned int, glm::vec3>& GetScales();
		static std::map<unsigned int, glm::vec3>& GetRotations();

		static glm::vec3* GetPosition(unsigned int id);
		static glm::vec3* GetScale(unsigned int id);
		static glm::vec3* GetRotation(unsigned int id);
	};

	struct LevelData {
		//only used when loading a scene or saving so its fine
		//but really this is probably the worst solution ever
		std::vector<std::string> names;
		std::vector<std::string> matNames;
		std::map<unsigned int, glm::vec3> positions;
		std::map<unsigned int, glm::vec3> scales;
		std::map<unsigned int, glm::vec3> rotations;
	};
}