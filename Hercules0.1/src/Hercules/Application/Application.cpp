#include "hcpch.h"
#include "Application.h"

#include "Hercules/Log/Log.h"
#include "Hercules/Input/Input.h"

#include <glad/glad.h>

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
			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			//if (InputManager::IsKeyPressed(HC_KEY_A))
			//{
				//HC_CORE_TRACE("A");
			//}

			//window->winUpdate();
			window->winUpdate();
			Update();
		}
	}
}
