#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Hercules {
	class Camera {
	public:
		Camera(glm::vec3 front);
		~Camera();

		void Look(double xpos, double ypos, glm::vec3 cameraFr);

		void Update(glm::vec3 front);

		glm::vec3 GetPos();
		glm::vec3 GetFront();
		glm::vec3 GetUp();
	private:
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::vec3 m_Front;

		float lastX = 960, lastY = 540;
		float pitch = 0.0f, yaw = 0.0f;
	};
}