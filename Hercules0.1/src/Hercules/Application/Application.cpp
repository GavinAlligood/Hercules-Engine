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

			SpatialRenderer::ClearColorBuffer(SceneManager::GetBackgroundColor());

			shader->Bind();
			UpdateLight();
			
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
				//shader->SetVec3("objectColor", glm::vec3(1.0f));
				shader->SetFloat("shininess",
					SceneManager::GetMaterialComponent((*it).first)->GetShininess());
				//shader->SetFloat("shininess", 32.0f);

				SpatialRenderer::DrawCube(*SceneManager::GetMaterialComponent((*it).first)->GetTexture(),
					glm::vec3((*it).second.GetPos()),
					glm::vec3((*it).second.GetScale()),
					glm::vec3((*it).second.GetRotation()),
					shader);
				
				//Note: i will need to use deffered shading later

				if (SceneManager::HasDirectionalLight((*it).first))
				{
					shader->SetVec3("dirLight.direction", (*it).second.GetRotation());
					shader->SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
					shader->SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
					shader->SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
				}
				/*else if (SceneManager::HasPointLight((*it).first))
				{
					shader->SetVec3("pointLights[0].position", 1.0f, 1.0f, 1.0f);
					shader->SetVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
					shader->SetVec3("pointLights[0].diffuse", glm::vec3(0.8f));
					shader->SetVec3("pointLights[0].specular", glm::vec3(1.0f));
					shader->SetFloat("pointLights[0].constant", 1.0f);
					shader->SetFloat("pointLights[0].linear", 0.09f);
					shader->SetFloat("pointLights[0].quadratic", 0.032);

					shader->SetVec3("pointLights[1].position", 15.0f, 5.0f, 0.0f);
					shader->SetVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
					shader->SetVec3("pointLights[1].diffuse", glm::vec3(0.8f));
					shader->SetVec3("pointLights[1].specular", glm::vec3(1.0f));
					shader->SetFloat("pointLights[1].constant", 1.0f);
					shader->SetFloat("pointLights[1].linear", 0.09f);
					shader->SetFloat("pointLights[1].quadratic", 0.032);
					
				}*/	
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