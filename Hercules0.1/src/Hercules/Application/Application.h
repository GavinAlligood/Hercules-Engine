#pragma once

#include "Core.h"

#include "Hercules/Core/Window/Window.h"

#include "Hercules/Scene/GL/Index/IndexBuffer.h"
#include "Hercules/Scene/GL/Vertex/VertexBuffer.h"
#include "Hercules/Scene/GL/Shader/Shader.h"

//Objects (will be in renderer)
#include "Hercules/Core/Objects/2D/Square/Square.h"
#include "Hercules/Core/Objects/2D/Triangle/Triangle.h"

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

		void checkClose();

		inline static Application& Get() { return *s_Instace; }
		inline Window& GetWindow() { return *window; }
	private:
		bool m_Running = true;
		static Application* s_Instace;
		Window* window = nullptr;

		//Entities test
		//Triangle* triangle = nullptr;
		Square* square = nullptr;
	};

	//Will be defined in client
	Application* CreateApplication();
}
