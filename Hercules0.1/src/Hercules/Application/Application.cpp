#include "hcpch.h"
#include "Application.h"

#include "Hercules/Core/Log/Log.h"
#include "Hercules/Core/Input/Input.h"

#include <glad/glad.h>

//Note:
//If any game is going to have some sort of typing, i will probably need a glfwKeyCallback function
//I should also add a way to not need glm::vec3 every time i use a vector

//So i still need to work on the 2D renderer but im going to focus on
//3d more since thats the kind of games I want to make in this engine

namespace Hercules {

#define HC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

	Application* Application::s_Instace = nullptr;

	Hercules::Application::Application()
	{
		s_Instace = this;

		window = new Window(600, 800);
	
		window->SetEventCallback(HC_BIND_EVENT_FN(Application::OnEvent));
	}

	Hercules::Application::~Application()
	{
		delete window;
	}

	void Application::Run()
	{
		Start();

		//in scene by default
		glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		/*std::vector<Entity> Entities;
		Entity ent, ent2, ent3;
		ent.SetTransform(1.0f, 0.0f, 0.0f);
		ent2.SetTransform(2.0f, 0.0f, 0.0f);
		ent3.SetTransform(3.0f, 0.0f, 0.0f);
		ent.SetColor(HC_COLOR_RED);
		ent2.SetColor(HC_COLOR_GREEN);
		ent3.SetColor(HC_COLOR_BLUE);
		ent.name = "Entity1";
		ent2.name = "Entity2";
		ent3.name = "Entity3";
		Entities.push_back(ent);
		Entities.push_back(ent2);
		Entities.push_back(ent3);*/

		/*for (const Entity& i : Entities)
		{
			HC_CORE_INFO(i.name);
		}*/

		while (m_Running)
		{
			checkClose();

			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glActiveTexture(GL_TEXTURE0);

			Update();

			window->winUpdate();
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