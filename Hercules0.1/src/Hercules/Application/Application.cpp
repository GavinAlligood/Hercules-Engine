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
		
		window->SetEventCallback(HC_BIND_EVENT_FN(Application::OnEvent));

		spatialRenderer = new SpatialRenderer();

		//speed
		sceneCamera = new Camera(3.0f);
	}

	Hercules::Application::~Application()
	{
		delete window;
		delete spatialRenderer;
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

		//in scene by default
		glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		float minecraftX = 0;

		Texture dirt("Assets/Textures/dirtMinecraft.jpg", 0, HC_IMG_JPG);
		Texture defaultTexture("Assets/Textures/default_texture.jpg", 0, HC_IMG_JPG);
		Texture amongus("Assets/Textures/amongus.png", 0, HC_IMG_PNG);
		Texture skeleton("Assets/Textures/drawnSkeleton.png", 0, HC_IMG_PNG);
		Texture sauron("Assets/Textures/EyeofSauronPixel.png", 0, HC_IMG_PNG);

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

#pragma region Minecraft
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
				InScene = false;
			}
			else if (InputManager::IsMousePressed(HC_MOUSE_BUTTON_1))
			{
				glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				InScene = true;
			}
#pragma endregion

			glActiveTexture(GL_TEXTURE0);

			window->winUpdate();
			Update();
		}
	}

	void Application::OnEvent(Event& e)
	{
		if (e.GetType() == EventType::CursorMoved && InScene)
		{
			CursorMovedEvent& c = (CursorMovedEvent&)e;
			GetCamera().Look(c.GetX(), c.GetY());
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