#include "hcpch.h"
#include "Application.h"

#include "Hercules/Core/Log/Log.h"
#include "Hercules/Core/Input/Input.h"

#include <glad/glad.h>

//Note:
//If any game is going to have some sort of typing, i will probably need a glfwKeyCallback function
//
//Users will need to input the path to the shaders folder. Its a terrible way to do this especially since its in the freaking hercules directory
//but im so tired so im just going to leave it like that for now. Ill probably come back in the future and fix that for sure
//I mean hey im 14 give me a break
//At least i know using absolute paths is horrible

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

		//triangle = new Triangle();
		square = new Square();
		square->SetTexture("C:/Users/Gavin/source/repos/HerculesEngine/Hercules/Sandbox/Assets/EyeofSauronPixel.png", HC_IMG_PNG);
		//square->SetColor(HC_COLOR_GREEN);
	}

	Hercules::Application::~Application()
	{
		delete window;

		//delete objects
		//delete triangle;
		delete square;
	}

	void Application::Run()
	{
		Start();
		while (m_Running)
		{
			checkClose();

			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			//Renderer will probably loop and call update on all
			//of the entities
			//bind shader
			//shader->Bind();
			//triangle->Update();
			
			square->Update();
			//glBindVertexArray(m_VertexArray);
			//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			//triangle->Draw();
			square->Draw();

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
