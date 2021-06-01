#include "hcpch.h"

#include "Camera.h"

Hercules::Camera::Camera(glm::vec3 front)
{
	
}

Hercules::Camera::~Camera()
{
}

void Hercules::Camera::Look(double xpos, double ypos, glm::vec3 cameraFr)
{
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
	cameraFr = glm::normalize(direction);
	HC_CORE_TRACE("{0}:{1}", xpos, ypos);
}

void Hercules::Camera::Update(glm::vec3 front)
{
	m_Front = front;
}

glm::vec3 Hercules::Camera::GetPos()
{
	return cameraPos;
}

glm::vec3 Hercules::Camera::GetFront()
{
	return cameraFront;
}

glm::vec3 Hercules::Camera::GetUp()
{
	return cameraUp;
}
