#include "hcpch.h"

#include "Camera.h"

Hercules::Camera::Camera(float cameraSpeed)
	: m_CameraSpeed(cameraSpeed)
{
	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
}

Hercules::Camera::~Camera()
{
}

void Hercules::Camera::Look(double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}

const void Hercules::Camera::MoveLeft()
{
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * m_CameraSpeed;
}

const void Hercules::Camera::MoveRight()
{
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * m_CameraSpeed;
}

const void Hercules::Camera::MoveForward()
{
	cameraPos += m_CameraSpeed * cameraFront;
}

const void Hercules::Camera::MoveBackward()
{
	cameraPos -= m_CameraSpeed * cameraFront;
}

const void Hercules::Camera::MoveUp()
{
	cameraPos += m_CameraSpeed * cameraUp;
}

const void Hercules::Camera::MoveDown()
{
	cameraPos -= m_CameraSpeed * cameraUp;
}
