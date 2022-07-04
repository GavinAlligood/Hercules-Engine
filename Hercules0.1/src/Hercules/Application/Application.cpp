#include "hcpch.h"
#include "Application.h"

#include "Hercules/Core/Log/Log.h"
#include "Hercules/Core/Input/Input.h"
#include "Hercules/Renderer/Model/Model.h"

#include <glad/glad.h>

//Note:
//I should also add a way to not need glm::vec3 every time i use a vector

//So i still need to work on the 2D renderer but im going to focus on
//3d more since thats the kind of games I want to make in this engine

namespace Hercules {

#define HC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

	Application* Application::s_Instace = nullptr;

	//TODO: Delete "isgame" pointless variable
	//Note isGame is used so I can still create applications that aren't games using hercules, like the project hub.
	Hercules::Application::Application(const char* name, std::string projectPath, bool isGame)
		: m_IsGame(isGame)
	{
		s_Instace = this;

		//This needs to go before shader creation
		window = new Window(name, 540, 960);

		if (isGame)
		{
			shader = new Shader(projectPath + "Assets/Shaders/Vertex.shader",
				projectPath + "Assets/Shaders/Fragment.shader");
		}
		
		window->SetEventCallback(HC_BIND_EVENT_FN(Application::OnApplicationEvent));
	}

	Hercules::Application::~Application()
	{
		delete window;
		if (m_IsGame) delete shader;
	}

	void Application::Run()
	{
		ImGuiInit();
		
		Start();

		//Anything called above this line will not be looped
		while (m_Running)
		{
			checkClose();

			//UpdateFramebuffer();

			if (m_IsGame)
			{
				shader->Bind();
				UpdateLight();
			}

			if (!m_Minimized)
			{
				Update();
				if (m_IsGame) Render();
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
		for (auto& i : SceneManager::GetMeshComponentList())
		{
			shader->SetVec3("objectColor",
				SceneManager::GetMaterialComponent(i.first)->GetColor());
			//shader->SetVec3("objectColor", glm::vec3(1.0f));
			shader->SetFloat("shininess",
				SceneManager::GetMaterialComponent(i.first)->GetShininess());
			//shader->SetFloat("shininess", 32.0f);

			//TransformComponent transform = *SceneManager::GetTransformComponent(i.first);
			//*SceneManager::GetTransformComponent(i.first)->GetPos()
			SpatialRenderer::DrawMesh(SceneManager::GetMeshComponent(i.first)->GetModel(),
				*SceneManager::GetMaterialComponent(i.first)->GetTexture(),
				glm::vec3(SceneManager::GetTransformComponent(i.first)->GetPos()),
				glm::vec3(SceneManager::GetTransformComponent(i.first)->GetScale()),
				glm::vec3(SceneManager::GetTransformComponent(i.first)->GetRotation()),
				shader);

			//TODO: This NEEDS to be moved eventually because lights have to work w/out meshes!
			if (SceneManager::HasDirectionalLight(i.first))
			{
				shader->SetVec3("dirLight.direction", SceneManager::GetTransformComponent(i.first)->GetRotation()); //1
				shader->SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
				shader->SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
				shader->SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
			}

			//Note: i will need to use deffered shading later

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

		//HC_CORE_TRACE(">====================<");
	}

	void Application::UpdateLight()
	{
		shader->SetVec3("viewPos", Camera::GetPos());
		//std::map<unsigned int, LightComponent>::iterator li;
		//for (li = SceneManager::GetLightComponentList().begin();
		//	li != SceneManager::GetLightComponentList().end(); ++li)
		//{
		//	//this is definately not going to work when i have multiple lights
		//	shader->SetVec3("lightColor", (*li).second.GetColor());
		//}

		//Just gonna use this for now
		/*for (auto& i : SceneManager::GetDirectionalLightList())
		{
			shader->SetVec3("lightColor", i.second.GetColor());
			shader->SetFloat("dirLight.ambient", i.second.GetAmbient());
		}*/
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
			HC_INFO("Exiting Hercules");
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