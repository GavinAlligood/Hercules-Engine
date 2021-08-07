#include "hcpch.h"

#include <glfw/glfw3.h>

#include "Camera.h"

namespace Hercules {
	
	CameraData data;

	glm::vec3 Camera::GetPos()
	{
		return data.cameraPos;
	}

	glm::vec3 Camera::GetFront()
	{
		return data.cameraFront;
	}

	glm::vec3 Camera::GetUp()
	{
		return data.cameraUp;
	}

	glm::mat4 Camera::GetProjectionMatrix()
	{
		return data.projection;
	}

	void Camera::SetAspectRatio(float width, float height)
	{
		data.aspectW = width;
		data.aspectH = height;
	}

	void Camera::UpdateAspectRatio()
	{
		data.projection = glm::perspective(glm::radians(45.0f), data.aspectW / data.aspectH, 0.1f, 100.0f);
	}

	std::pair<float, float> Camera::GetAspectRatio()
	{
		return std::pair<float, float>(data.aspectW, data.aspectH);
	}

	void Camera::Init(float cameraSpeed)
	{
		data.cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		data.cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		data.cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		data.m_CameraSpeed = cameraSpeed;

		data.projection = glm::perspective(glm::radians(45.0f), data.aspectW / data.aspectH, 0.1f, 100.0f);
	}

	void Hercules::Camera::Look(double xpos, double ypos)
	{
		data.m_DeltaSpeed = data.m_CameraSpeed * data.deltaTime;

		if (data.firstMouse)
		{
			data.lastX = xpos;
			data.lastY = ypos;
			data.firstMouse = false;
		}

		float xoffset = xpos - data.lastX;
		float yoffset = data.lastY - ypos; // reversed since y-coordinates range from bottom to top
		data.lastX = xpos;
		data.lastY = ypos;

		const float sensitivity = 0.1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		data.yaw += xoffset;
		data.pitch += yoffset;

		if (data.pitch > 89.0f)
			data.pitch = 89.0f;
		if (data.pitch < -89.0f)
			data.pitch = -89.0f;
		
		glm::vec3 direction;

		direction.x = cos(glm::radians(data.yaw)) * cos(glm::radians(data.pitch));
		direction.y = sin(glm::radians(data.pitch));
		direction.z = sin(glm::radians(data.yaw)) * cos(glm::radians(data.pitch));
		data.cameraFront = glm::normalize(direction);

		//data.firstMouse = true;
	}

	void Camera::SetFirstMouse(bool status)
	{
		data.firstMouse = status;
	}

	const void Hercules::Camera::UpdateTime()
	{
		float currentFrame = glfwGetTime();
		data.deltaTime = currentFrame - data.lastFrame;
		data.lastFrame = currentFrame;
	}

	const void Hercules::Camera::MoveLeft(int speedIncrement)
	{
		data.cameraPos -= glm::normalize(glm::cross(data.cameraFront, data.cameraUp)) * (data.m_DeltaSpeed * speedIncrement);
	}

	const void Hercules::Camera::MoveRight(int speedIncrement)
	{
		data.cameraPos += glm::normalize(glm::cross(data.cameraFront, data.cameraUp)) * (data.m_DeltaSpeed * speedIncrement);
	}

	const void Hercules::Camera::MoveForward(int speedIncrement)
	{
		data.cameraPos += (data.m_DeltaSpeed * speedIncrement) * data.cameraFront;
	}

	const void Hercules::Camera::MoveBackward(int speedIncrement)
	{
		data.cameraPos -= (data.m_DeltaSpeed * speedIncrement) * data.cameraFront;
	}

	const void Hercules::Camera::MoveUp(int speedIncrement)
	{
		data.cameraPos += (data.m_DeltaSpeed * speedIncrement) * data.cameraUp;
	}

	const void Hercules::Camera::MoveDown(int speedIncrement)
	{
		data.cameraPos -= (data.m_DeltaSpeed * speedIncrement) * data.cameraUp;
	}

}
