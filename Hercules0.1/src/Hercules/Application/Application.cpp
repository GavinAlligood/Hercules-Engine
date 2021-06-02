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

		window = new Window(600, 800);

		//speed
		sceneCamera = new Camera(5.0f);

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

		//maybe remove this 0 option i dont see how its doing anything currently
		Texture defaultTexture("Assets/Textures/default_texture.jpg", 0, HC_IMG_JPG);
		Texture amongus("Assets/Textures/amongus.png", 0, HC_IMG_PNG);
		Texture skeleton("Assets/Textures/drawnSkeleton.png", 0, HC_IMG_PNG);
		Texture dirt("Assets/Textures/dirtMinecraft.jpg", 0, HC_IMG_JPG);

		glfwSetCursorPosCallback(window->GetWindow(), [](GLFWwindow* window, double xpos, double ypos)
		{
				Application& data = *(Application*)glfwGetWindowUserPointer(window);

				data.GetCamera().Look(xpos, ypos);
		});

		float minecraftX = 0;

		while (m_Running)
		{
			checkClose();

			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			sceneCamera->UpdateTime();

#pragma region Movement
			if (InputManager::IsKeyPressed(HC_KEY_W))
			{
				GetCamera().MoveForward();
			}
			else if (InputManager::IsKeyPressed(HC_KEY_S))
			{
				GetCamera().MoveBackward();
			}
			if (InputManager::IsKeyPressed(HC_KEY_A))
			{
				GetCamera().MoveLeft();
			}
			else if (InputManager::IsKeyPressed(HC_KEY_D))
			{
				GetCamera().MoveRight();
			}
			if (InputManager::IsKeyPressed(HC_KEY_SPACE))
			{
				GetCamera().MoveUp();
			}
			else if (InputManager::IsKeyPressed(HC_KEY_LEFT_ALT))
			{
				GetCamera().MoveDown();
			}

			if (InputManager::IsKeyPressed(HC_KEY_ESCAPE))
			{
				glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			else if (InputManager::IsMousePressed(HC_MOUSE_BUTTON_1))
			{
				glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
#pragma endregion
			glActiveTexture(GL_TEXTURE0);

#pragma region minecraft
			for (int i = 0; i < 4; i++)
			{
				
				spatialRenderer->DrawCube(dirt,
					glm::vec3(x + minecraftX, y, z - 5.0f),
					glm::vec3(0.5f, 0.5f, 0.5f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec4(HC_COLOR_WHITE),
					SCENE_CAMERA);
				minecraftX += 0.5;
			}
			minecraftX = 0;
			
			for (int i = 0; i < 4; i++)
			{

				spatialRenderer->DrawCube(dirt,
					glm::vec3(x + minecraftX, y, z - 4.5f),
					glm::vec3(0.5f, 0.5f, 0.5f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec4(HC_COLOR_WHITE),
					SCENE_CAMERA);
				minecraftX += 0.5;
			}
			minecraftX = 0;

			for (int i = 0; i < 4; i++)
			{

				spatialRenderer->DrawCube(dirt,
					glm::vec3(x + minecraftX, y, z - 4.0f),
					glm::vec3(0.5f, 0.5f, 0.5f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec4(HC_COLOR_WHITE),
					SCENE_CAMERA);
				minecraftX += 0.5;
			}
			minecraftX = 0;

			for (int i = 0; i < 4; i++)
			{

				spatialRenderer->DrawCube(dirt,
					glm::vec3(x + minecraftX, y, z - 3.5f),
					glm::vec3(0.5f, 0.5f, 0.5f),
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec4(HC_COLOR_WHITE),
					SCENE_CAMERA);
				minecraftX += 0.5;
			}
			minecraftX = 0;
#pragma endregion

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
}