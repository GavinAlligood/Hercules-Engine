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

#define HC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

	Application* Application::s_Instace = nullptr;

	Hercules::Application::Application()
	{
		s_Instace = this;

		window = new Window(600, 800);
		
		shader = new Shader("Assets/Shaders/Vertex.shader",
			"Assets/Shaders/Fragment.shader");

		//spatialRenderer = new SpatialRenderer();
		sceneCamera = new Camera(3.0f);

		window->SetEventCallback(HC_BIND_EVENT_FN(Application::OnEvent));
	}

	Hercules::Application::~Application()
	{
		delete window;
		//delete spatialRenderer;
		delete sceneCamera;
		delete shader;
	}

	void Application::Run()
	{
		Start();

		//in scene by default
		glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		std::vector<Entity> Entities;
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
		Entities.push_back(ent3);

		Texture defaultTex = Texture("Assets/Textures/default_texture.jpg", 0, HC_IMG_JPG);
		Texture skeleton = Texture("Assets/Textures/drawnSkeleton.png", 0, HC_IMG_PNG);

		SpatialRenderer::Init();

		for (const Entity& i : Entities)
		{
			HC_CORE_INFO(i.name);
		}

		while (m_Running)
		{
			checkClose();

			sceneCamera->UpdateTime();

			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glActiveTexture(GL_TEXTURE0);

			if (InputManager::IsKeyPressed(HC_KEY_W))
			{
				sceneCamera->MoveForward();
			}
			else if (InputManager::IsKeyPressed(HC_KEY_S))
			{
				sceneCamera->MoveBackward();
			}
			if (InputManager::IsKeyPressed(HC_KEY_A))
			{
				sceneCamera->MoveLeft();
			}
			else if (InputManager::IsKeyPressed(HC_KEY_D))
			{
				sceneCamera->MoveRight();
			}
			if (InputManager::IsKeyPressed(HC_KEY_SPACE))
			{
				sceneCamera->MoveUp();
			}
			else if (InputManager::IsKeyPressed(HC_KEY_LEFT_ALT))
			{
				sceneCamera->MoveDown();
			}

			for (float i = 0.0; i < 7.0; i++)
			{
				SpatialRenderer::DrawCube(defaultTex,
					glm::vec3(0.0f, i, 0.0f),
					glm::vec3(1.0f),
					glm::vec3(0.0f),
					glm::vec4(HC_COLOR_WHITE),
					SCENE_CAMERA, shader);
			}

			for (float i = 1.0f; i < 3.0f; i++)
			{
				SpatialRenderer::DrawCube(defaultTex,
					glm::vec3(i, 5.0f, 0.0f),
					glm::vec3(1.0f),
					glm::vec3(0.0f),
					glm::vec4(HC_COLOR_WHITE),
					SCENE_CAMERA, shader);
			}

			for (float i = 1.0f; i < 3.0f; i++)
			{
				SpatialRenderer::DrawCube(defaultTex,
					glm::vec3(-i, 5.0f, 0.0f),
					glm::vec3(1.0f),
					glm::vec3(0.0f),
					glm::vec4(HC_COLOR_WHITE),
					SCENE_CAMERA, shader);
			}

			Update();

			window->winUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		if (e.GetType() == EventType::CursorMoved)
		{
			CursorMovedEvent& c = (CursorMovedEvent&)e;
			sceneCamera->Look(c.GetX(), c.GetY());
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