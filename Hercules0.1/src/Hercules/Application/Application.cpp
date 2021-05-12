#include "hcpch.h"
#include "Application.h"

#include "Hercules/Log/Log.h"
#include "Hercules/Input/Input.h"

#include <glad/glad.h>

//Note:
//If any game is going to have some sort of typing, i will probably need a glfwKeyCallback function

namespace Hercules {

	Application* Application::s_Instace = nullptr;
	InputManager* InputManager::s_Instace = new InputManager();

	Hercules::Application::Application()
	{
		s_Instace = this;
		window = new Window(600, 800);
		/*unsigned int id;
		glGenVertexArrays(1, &id);*/
	}

	Hercules::Application::~Application()
	{
		delete window;
	}

	void Application::Run()
	{
		Start();
		while (m_Running)
		{
			checkClose();

			glClearColor(0.2f, 0.2f, 0.2f, 1);
			//renderer->Clear();
			//renderer.draw();
			glClear(GL_COLOR_BUFFER_BIT);
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
