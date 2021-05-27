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
		cube->SetTexture("Assets/Textures/drawnSkeleton.png", HC_IMG_PNG);
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
		while (m_Running)
		{
			checkClose();

			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			//Renderer will probably loop and call update on all
			//of the entities
			//bind shader
			//shader->Bind();

			cube->Rotate(30.0f, 1.0f, 0.0f, 0.0f);
			//need to translate last
			cube->Translate(x, y, z);
			
			//cube->Rotate(40.0f, 0.0f, 1.0f, 0.0f);

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

			/*float x = InputManager::GetMouseX();
			float y = InputManager::GetMouseY();
			if (firstMouse)
			{
				lastX = x;
				lastY = y;
				firstMouse = false;
			}
			float xoffset = x - lastX;
			float yoffset = lastY - y;

			float sensitivity = 0.1f;
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
			direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));*/

			//glBindVertexArray(m_VertexArray);
			//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			cube->Draw();

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
