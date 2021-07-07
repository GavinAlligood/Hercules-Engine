#include "hcpch.h"
#include "Application.h"

#include "Hercules/Core/Log/Log.h"
#include "Hercules/Core/Input/Input.h"

#include <glad/glad.h>

//Note:
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

		window->SetEventCallback(HC_BIND_EVENT_FN(Application::OnApplicationEvent));
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
		//glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		ImGuiInit();

		while (m_Running)
		{
			checkClose();

			UpdateFramebuffer();

			//make this a render command
			glClearColor(0.3f, 0.3f, 0.7f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			shader->Bind();
			UpdateLight();

			//glActiveTexture(GL_TEXTURE0);
			
			if (!m_Minimized)
			{
				Update();
				Render();
			}
			
			ImGuiRender();

			window->winUpdate();
		}
		
	}

	void Application::OnApplicationEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizeEvent>(HC_BIND_EVENT_FN(Application::OnWindowResize));

		OnEvent(e);
	}

	void Application::Render()
	{
		//i could possibly use entities here later
		if (SceneManager::GetTransformComponentList().size() != 0)
		{
			std::map<unsigned int, TransformComponent>::iterator it;
			for (it = SceneManager::GetTransformComponentList().begin();
				it != SceneManager::GetTransformComponentList().end(); ++it)
			{
				shader->SetVec3("objectColor", 
					SceneManager::GetMaterialComponent((*it).first)->GetColor());
				SpatialRenderer::DrawCube(SceneManager::GetMaterialComponent((*it).first)->GetTexture(),
					glm::vec3((*it).second.GetPos()),
					glm::vec3((*it).second.GetScale()),
					glm::vec3((*it).second.GetRotation()),
					glm::vec4(SceneManager::GetMaterialComponent((*it).first)->GetColor(), 1.0f),
					shader);
				
				//HC_CORE_TRACE("Iteration ID: {0}", (*it).second.GetTexture().GetID());
				
				if (SceneManager::HasLightComponent((*it).first))
				{
					//this is definately not going to work when i have multiple lights
					shader->SetVec3("lightPos", (*it).second.GetPos());
				}
			}
		}
	}

	void Application::UpdateLight()
	{
		shader->SetVec3("viewPos", Camera::GetPos());
		std::map<unsigned int, LightComponent>::iterator li;
		for (li = SceneManager::GetLightComponentList().begin();
			li != SceneManager::GetLightComponentList().end(); ++li)
		{
			//this is definately not going to work when i have multiple lights
			shader->SetVec3("lightColor", (*li).second.GetColor());
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	//turn this into an event
	void Application::checkClose()
	{
		if (glfwWindowShouldClose(window->GetWindow()))
		{
			m_Running = false;
		}
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		//minimized
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		//Will probably have to change this somehow
		SpatialRenderer::WindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}