#include "hcpch.h"
#include "Application.h"

#include "Hercules/Core/Log/Log.h"
#include "Hercules/Core/Input/Input.h"

#include <glad/glad.h>

//Note:
//If any game is going to have some sort of typing, i will probably need a glfwKeyCallback function

//So i still need to work on the 2D renderer but im going to focus on
//3d more since thats the kind of games I want to make in this engine

namespace Hercules {

	Application* Application::s_Instace = nullptr;
	InputManager* InputManager::s_Instace = new InputManager();

	Hercules::Application::Application()
	{
		s_Instace = this;

		sceneCamera = new Camera(glm::vec3(1.0f));

		window = new Window(600, 800);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		spatialRenderer = new SpatialRenderer();

		glfwSetWindowUserPointer(window->GetWindow(), this);
	}

	Hercules::Application::~Application()
	{
		delete window;
		delete spatialRenderer;
		delete sceneCamera;
	}

	void Application::Run()
	{
		Start();

		float x = 0.1f;
		float y = 0.0f;
		float z = -3.0f;

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		float speed = 0.0;

		Texture defaultTexture("Assets/Textures/default_texture.jpg", 0, HC_IMG_JPG);
		Texture amongus("Assets/Textures/amongus.png", 0, HC_IMG_PNG);
		Texture skeleton("Assets/Textures/drawnSkeleton.png", 0, HC_IMG_PNG);
		
		//void mouse_callback(GLFWwindow * window, double xpos, double ypos);

		//glfwSetCursorPosCallback(window->GetWindow(), callback);

		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

		//sceneCamera->Update(cameraFront);

		glfwSetCursorPosCallback(window->GetWindow(), [](GLFWwindow* window, double xpos, double ypos)
		{
				Application& data = *(Application*)glfwGetWindowUserPointer(window);

				//data.GetCamera().Look(xpos, ypos, data.cameraFront);
				data.Look(xpos, ypos);
		});

		while (m_Running)
		{
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;


			//camera front isnt updating blin!!!
			//sceneCamera->Update(cameraFront);

			checkClose();

			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			speed = 5.0f * deltaTime;

			if (InputManager::IsKeyPressed(HC_KEY_W))
			{
				cameraPos += speed * cameraFront;
			}
			else if (InputManager::IsKeyPressed(HC_KEY_S))
			{
				cameraPos -= speed * cameraFront;
			}
			if (InputManager::IsKeyPressed(HC_KEY_A))
			{
				cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
			}
			else if (InputManager::IsKeyPressed(HC_KEY_D))
			{
				cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
			}
			if (InputManager::IsKeyPressed(HC_KEY_SPACE))
			{
				cameraPos += speed * cameraUp;
			}
			else if (InputManager::IsKeyPressed(HC_KEY_LEFT_ALT))
			{
				cameraPos -= speed * cameraUp;
			}

			if (InputManager::IsKeyPressed(HC_KEY_ESCAPE))
			{
				glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			else if (InputManager::IsMousePressed(HC_MOUSE_BUTTON_1))
			{
				glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}

			glActiveTexture(GL_TEXTURE0);

			spatialRenderer->DrawCube(defaultTexture,
				glm::vec3(x, y, z - 5.0f),
				glm::vec3(1.0f, 1.0f, 1.0f),
				glm::vec3(0.0f, 25.0f, 60.0f),
				glm::vec4(HC_COLOR_WHITE),
				cameraPos, cameraFront, cameraUp);

			spatialRenderer->DrawCube(skeleton,
				glm::vec3(x + 5.0f, y, z - 5.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(20.0f, 45.0f, 0.0f),
				glm::vec4(HC_COLOR_BLUE),
				cameraPos, cameraFront, cameraUp);
			
			spatialRenderer->DrawCube(skeleton,
				glm::vec3(x, y + 5.0f, z - 5.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(45.0f, 90.0f, 90.0f),
				glm::vec4(HC_COLOR_WHITE),
				cameraPos, cameraFront, cameraUp);

			spatialRenderer->DrawCube(skeleton,
				glm::vec3(x + 2.0f, y - 3.0f, z - 5.0f),
				glm::vec3(0.5f, 1.5f, 0.5f),
				glm::vec3(45.0f, 0.0f, 25.0f),
				glm::vec4(HC_COLOR_RED),
				cameraPos, cameraFront, cameraUp);

			spatialRenderer->DrawCube(defaultTexture,
				glm::vec3(x - 5.0f, y, z - 5.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(0.0f, 60.0f, 0.0f),
				glm::vec4(HC_COLOR_GREEN),
				cameraPos, cameraFront, cameraUp);

			spatialRenderer->DrawCube(defaultTexture,
				glm::vec3(x, y - 7.0f, z + 5.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(15.0f, 15.0f, 15.0f),
				glm::vec4(HC_COLOR_GREEN),
				cameraPos, cameraFront, cameraUp);

			window->winUpdate();
			Update();
		}
	}

	void Application::checkClose()
	{
		if (glfwWindowShouldClose(window->GetWindow()))
		{
			m_Running = false;
		}
	}

	void Application::Look(double xpos, double ypos)
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
		cameraFront = glm::normalize(direction);
		//HC_CORE_TRACE("{0}:{1}", xpos, ypos);
	}

}


