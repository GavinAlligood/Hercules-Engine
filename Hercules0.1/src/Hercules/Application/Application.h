#pragma once

#include "Core.h"

#include "Hercules/Core/Window/Window.h"

#include "Hercules/Renderer/GL/Index/IndexBuffer.h"
#include "Hercules/Renderer/GL/Vertex/VertexBuffer.h"
#include "Hercules/Renderer/GL/Shader/Shader.h"

#include "Hercules/Core/Events/Event.h"

namespace Hercules {

	class Application
	{
	public:
		Application();
		//will be inherited from
		virtual ~Application();

		void Run();

		virtual void Start() = 0;
		virtual void Update() = 0;
		virtual void OnEvent(Event& e) = 0;

		void checkClose();

		inline static Application& Get() { return *s_Instace; }
		inline Window& GetWindow() { return *window; }
	private:
		bool m_Running = true;
		static Application* s_Instace;
		Window* window = nullptr;

		bool InScene = true;
	};

	//Will be defined in client
	Application* CreateApplication();

	class Entity {
	public:
		glm::vec3 transform = glm::vec3(0.0f);
		glm::vec4 color = glm::vec4(1.0f);
		
		std::string name;

		void SetColor(float r, float g, float b, float a)
		{
			m_R = r;
			m_G = g;
			m_B = b;
			m_A = a;
			color = glm::vec4(r, g, b, a);
		}

		void SetTransform(float x, float y, float z)
		{
			transform = glm::vec3(x, y, z);
		}

	private:
		float m_R, m_G, m_B, m_A;
	};
}