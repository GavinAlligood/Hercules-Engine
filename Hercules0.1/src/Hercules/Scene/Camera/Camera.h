#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Hercules {
	class Camera {
	public:
		Camera() {};
		~Camera() {};

		static void Look(double xpos, double ypos);

		static void SetFirstMouse(bool status);

		static glm::vec3 GetPos();
		static glm::vec3 GetFront();
		static glm::vec3 GetUp();

		static glm::mat4 GetProjectionMatrix();
		
		static void SetAspectRatio(float width, float height);
		static void UpdateAspectRatio();
		static std::pair<float, float> GetAspectRatio();

		static void Init(float cameraSpeed);

		static const void UpdateTime();

		static const void MoveLeft(int speedIncrement);
		static const void MoveRight(int speedIncrement);
		static const void MoveForward(int speedIncrement);
		static const void MoveBackward(int speedIncrement);
		static const void MoveUp(int speedIncrement);
		static const void MoveDown(int speedIncrement);
	};

	struct CameraData {
		//480, 270
		float lastX = 1920.0f/2.0f, lastY = 1080.0f/2.0f;
		float pitch = 0.0f, yaw = 0.0f;

		bool firstMouse = true;
		double currentX = 0.0;
		double currentY = 0.0;

		glm::vec3 cameraPos = glm::vec3(1.0f);
		glm::vec3 cameraFront = glm::vec3(1.0f);
		glm::vec3 cameraUp = glm::vec3(1.0f);

		float aspectW = 960.0f, aspectH = 540.0f;

		glm::mat4 projection = glm::mat4(1.0f);

		float m_CameraSpeed = 0.0f;
		float m_DeltaSpeed = 0.0f;
		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
	};

}