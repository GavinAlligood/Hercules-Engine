#include "hcpch.h"
#include "Application.h"

#include "Hercules/Core/Log/Log.h"
#include "Hercules/Core/Input/Input.h"

#include <glad/glad.h>

//Note:
//If any game is going to have some sort of typing, i will probably need a glfwKeyCallback function
//

//Todo:
//I shoudl make a class for vertex arrays
//I need to be able to render colors AND materials

namespace Hercules {

	Application* Application::s_Instace = nullptr;
	InputManager* InputManager::s_Instace = new InputManager();

	Hercules::Application::Application()
	{
		s_Instace = this;
		window = new Window(600, 800);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		spatialRenderer = new SpatialRenderer();
		flatRenderer = new FlatRenderer();
	}

	Hercules::Application::~Application()
	{
		delete window;

		delete spatialRenderer;
		delete flatRenderer;
	}

	void Application::Run()
	{
		Start();

		float x = 0.0f;
		float y = 0.0f;
		float z = -3.0f;

		//will use delta time
		float speed = 0.05;

		Texture defaultTexture("Assets/Textures/default_texture.jpg", 0, HC_IMG_JPG);
		Texture amongus("Assets/Textures/amongus.png", 0, HC_IMG_PNG);
		Texture skeleton("Assets/Textures/drawnSkeleton.png", 0, HC_IMG_PNG);

		while (m_Running)
		{
			checkClose();

			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			if (InputManager::IsKeyPressed(HC_KEY_W))
			{
				z += speed;
			}
			else if (InputManager::IsKeyPressed(HC_KEY_S))
			{
				z -= speed;
			}
			if (InputManager::IsKeyPressed(HC_KEY_A))
			{
				x += speed;
			}
			else if (InputManager::IsKeyPressed(HC_KEY_D))
			{
				x -= speed;
			}
			if (InputManager::IsKeyPressed(HC_KEY_SPACE))
			{
				y -= speed;
			}
			else if (InputManager::IsKeyPressed(HC_KEY_LEFT_ALT))
			{
				y += speed;
			}

			glActiveTexture(GL_TEXTURE0);

			spatialRenderer->DrawCube(defaultTexture,
				glm::vec3(x, y, z - 5.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(0.0f, 25.0f, 60.0f),
				glm::vec4(HC_COLOR_WHITE));

			spatialRenderer->DrawCube(skeleton,
				glm::vec3(x + 5.0f, y, z - 5.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(20.0f, 45.0f, 0.0f),
				glm::vec4(HC_COLOR_WHITE));

			spatialRenderer->DrawCube(skeleton,
				glm::vec3(x, y + 5.0f, z - 5.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(45.0f, 90.0f, 90.0f),
				glm::vec4(HC_COLOR_WHITE));

			spatialRenderer->DrawCube(skeleton,
				glm::vec3(x + 2.0f, y - 3.0f, z - 5.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(45.0f, 0.0f, 25.0f),
				glm::vec4(HC_COLOR_WHITE));

			spatialRenderer->DrawCube(defaultTexture,
				glm::vec3(x - 5.0f, y, z - 5.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(0.0f, 60.0f, 0.0f),
				glm::vec4(HC_COLOR_WHITE));

			spatialRenderer->DrawCube(defaultTexture,
				glm::vec3(x, y - 7.0f, z + 5.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(15.0f, 15.0f, 15.0f),
				glm::vec4(HC_COLOR_GREEN));

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
