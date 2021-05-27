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

		cube = new Cube();
		//no need for absolute path, can just use Assets/ because thats in the Sandbox project
		//square->SetColor(HC_COLOR_GREEN);
	}

	Hercules::Application::~Application()
	{
		delete window;

		//delete objects
		delete cube;
	}

	void Application::Run()
	{
		Start();
		float x = 0.0f;
		float y = 0.0f;
		float z = -3.0f;
		bool firstMouse = true;
		float lastX = 400, lastY = 300;
		float yaw = -90.0f, pitch = 0;

		Texture tex("Assets/Textures/drawnSkeleton.png", 0);
		
		Texture texx("Assets/Textures/EyeofSauronPixel.png", 1);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		while (m_Running)
		{
			checkClose();

			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			//Renderer will probably loop and call update on all
			//of the entities
			//bind shader
			//shader->Bind();

			if (InputManager::IsKeyPressed(HC_KEY_W))
			{
				z += 0.01;
			}
			else if (InputManager::IsKeyPressed(HC_KEY_S))
			{
				z -= 0.01;
			}
			if (InputManager::IsKeyPressed(HC_KEY_A))
			{
				x += 0.01;
			}
			else if (InputManager::IsKeyPressed(HC_KEY_D))
			{
				x -= 0.01;
			}
			if (InputManager::IsKeyPressed(HC_KEY_SPACE))
			{
				y -= 0.01;
			}
			else if (InputManager::IsKeyPressed(HC_KEY_LEFT_ALT))
			{
				y += 0.01;
			}

			glActiveTexture(GL_TEXTURE0);
			tex.Bind();

			cube->Draw(tex, glm::vec3(-0.7f, 0.0f, -3.0f),
				glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

			//glActiveTexture(GL_TEXTURE0);
			texx.Bind();

			cube->Draw(texx, glm::vec3(0.7f, 0.0f, -3.0f),
				glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.5f, 0.0f, 0.0f));

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
