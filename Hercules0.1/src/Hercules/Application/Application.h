#pragma once

#include "Core.h"

#include "Hercules/Core/Window/Window.h"

#include "Hercules/Scene/GL/Index/IndexBuffer.h"
#include "Hercules/Scene/GL/Vertex/VertexBuffer.h"
#include "Hercules/Scene/GL/Shader/Shader.h"

#include "Hercules/Renderer/2D/2DRenderer.h"
#include "Hercules/Renderer/3D/3DRenderer.h"

#include "Hercules/Scene/Camera/Camera.h"

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

		void Look(double xpos, double ypos);

		glm::vec3 cameraFront;

		inline static Application& Get() { return *s_Instace; }
		inline Window& GetWindow() { return *window; }
		inline Camera& GetCamera() { return *sceneCamera; }
	private:
		bool m_Running = true;
		static Application* s_Instace;
		Window* window = nullptr;

		SpatialRenderer* spatialRenderer = nullptr;

		Camera* sceneCamera = nullptr;

		unsigned int m_VertexArray;

		float lastX = 960, lastY = 540;
		float pitch = 0.0f, yaw = 0.0f;
	};

	//Will be defined in client
	Application* CreateApplication();
}
