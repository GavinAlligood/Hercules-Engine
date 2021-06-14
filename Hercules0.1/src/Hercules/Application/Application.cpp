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

		window = new Window(540, 960);

		shader = new Shader("Assets/Shaders/Vertex.shader",
			"Assets/Shaders/Fragment.shader");

		window->SetEventCallback(HC_BIND_EVENT_FN(Application::OnEvent));
	}

	Hercules::Application::~Application()
	{
		delete window;
		delete shader;
	}

	void Application::Run()
	{
		Start();

		//in scene by default
		glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		//Wireframe
		//Also make a macro for this
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		while (m_Running)
		{
			checkClose();
			CalculateFrameRate();

			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//So it seems theres only one 'object color'
			//i should set this in transform (for now)
			//since thats currently where i have color stored for objects

			shader->SetVec3("viewPos", Camera::GetPos());
			//shader->SetVec3("lightColor", glm::vec3(1.0f));
			UpdateLight();
			//shader->SetVec3("objectColor", 0.2f, 1.0f, 0.3f);// shade of green, will make this apart of component later
			//shader->SetVec3("lightPos", -1.2f, 1.0f, -6.0f); //am entering it manually rn for the sake of testing

			glActiveTexture(GL_TEXTURE0);

			Update();
			Render();

			window->winUpdate();
		}
	}

	void Application::Render()
	{
		std::map<unsigned int, TransformComponent>::iterator it;
		for (it = SceneManager::GetTransformComponentList().begin();
			it != SceneManager::GetTransformComponentList().end(); ++it)
		{
			//0.2f 1.0f 0.3f
			shader->SetVec3("objectColor", (*it).second.GetColor());
			SpatialRenderer::DrawCube((*it).second.GetTexture(),
				glm::vec3((*it).second.GetPos()),
				glm::vec3((*it).second.GetScale()),
				glm::vec3((*it).second.GetRotation()),
				glm::vec4((*it).second.GetColor()),
				SCENE_CAMERA, shader);

			if (SceneManager::HasLightComponent((*it).second.GetId()))
			{
				shader->SetVec3("lightPos", (*it).second.GetPos());
			}
		}
		
	}

	void Application::UpdateLight()
	{
		std::map<unsigned int, LightComponent>::iterator li;
		for (li = SceneManager::GetLightComponentList().begin();
			li != SceneManager::GetLightComponentList().end(); ++li)
		{
			//this is definately not going to work when i have multiple lights
			shader->SetVec3("lightColor", (*li).second.GetColor());
		}
	}

	void Application::checkClose()
	{
		if (glfwWindowShouldClose(window->GetWindow()))
		{
			m_Running = false;
		}
	}

	//Make a macro to control this
	void Application::CalculateFrameRate()
	{
		static float framesPerSecond = 0.0f;
		static float lastTime = 0.0f;
		float currentTime = GetTickCount64() * 0.001f;
		++framesPerSecond;
		if (currentTime - lastTime > 1.0f)
		{
			lastTime = currentTime;
			HC_CORE_INFO("Current Frames Per Second: {0}", (int)framesPerSecond);
			framesPerSecond = 0;
		}
	}
}