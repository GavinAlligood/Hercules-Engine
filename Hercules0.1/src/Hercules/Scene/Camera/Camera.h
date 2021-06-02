#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Hercules {
	class Camera {
	public:
		Camera(float cameraSpeed);
		~Camera();

		void Look(double xpos, double ypos);

		inline glm::vec3* GetPos() { return &cameraPos; }
		inline glm::vec3* GetFront() { return &cameraFront; }
		inline glm::vec3* GetUp() { return &cameraUp; }

		const void MoveLeft();
		const void MoveRight();
		const void MoveForward();
		const void MoveBackward();
		const void MoveUp();
		const void MoveDown();
	private:
		float lastX = 960, lastY = 540;
		float pitch = 0.0f, yaw = 0.0f;

		bool firstMouse = true;

		glm::vec3 cameraPos = glm::vec3(1.0f);
		glm::vec3 cameraFront = glm::vec3(1.0f);
		glm::vec3 cameraUp = glm::vec3(1.0f);

		float m_CameraSpeed = 0.0f;
	};

#define SCENE_CAMERA *GetCamera().GetPos(), *GetCamera().GetFront(), *GetCamera().GetUp()
}