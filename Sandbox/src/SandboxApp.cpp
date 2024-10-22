#include <../Hercules.h>

using namespace Hercules;

//i need to clean up some uses of glm::vec3

//RUNTIME

class Sandbox : public Hercules::Application
{
public:
	Sandbox(const char* name)
		: Application(name)
	{
		glfwSetInputMode(Application::Get().GetWindow().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		SpatialRenderer::Init();
		Camera::Init(5.0f);
	}

	~Sandbox()
	{
		SpatialRenderer::End();
	}

	void PlayerMovement()
	{
		if (InputManager::IsKeyPressed(HC_KEY_W))
		{
			Camera::MoveForward(1);
		}
		else if (InputManager::IsKeyPressed(HC_KEY_S))
		{
			Camera::MoveBackward(1);
		}
		if (InputManager::IsKeyPressed(HC_KEY_A))
		{
			Camera::MoveLeft(1);
		}
		else if (InputManager::IsKeyPressed(HC_KEY_D))
		{
			Camera::MoveRight(1);
		}
		if (InputManager::IsKeyPressed(HC_KEY_SPACE))
		{
			Camera::MoveUp(1);
		}
		else if (InputManager::IsKeyPressed(HC_KEY_LEFT_ALT))
		{
			Camera::MoveDown(1);
		}
	}

	void Sandbox::Start() override
	{
		HC_INFO("Start");
		//					   component id        Entity ID
		//SceneManager::NewComponent(DemoComponent(1));
		//SceneManager::NewComponent(DemoComponent(2));
		//SceneManager::NewComponent(DemoComponent(5));
		//SceneManager::NewComponent(TransformComponent(1, glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f), dirt, glm::vec4(HC_COLOR_WHITE)));
		//SceneManager::NewComponent(TransformComponent(2, glm::vec3(-1.0f, 1.0f, 0.5f), glm::vec3(0.5f), glm::vec3(0.0f), dirt, glm::vec4(HC_COLOR_GREEN)));
		//SceneManager::NewComponent(TransformComponent(3, glm::vec3(2.0f, 0.5f, 0.0f), glm::vec3(1.0f), glm::vec3(25.0f, 45.0f, 0.0f), dirt, glm::vec4(HC_COLOR_WHITE)));
		//SceneManager::NewComponent(TransformComponent(5, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(45.0f, 0.0f, 0.0f), defaultTex, glm::vec4(HC_COLOR_WHITE)));
		//SceneManager::NewComponent(TransformComponent(6, glm::vec3(-1.2f, 1.0f, -6.0f), glm::vec3(1.0f), glm::vec3(0.0f), defaultTex, glm::vec4(HC_COLOR_WHITE)));
		//SceneManager::NewComponent(LightComponent(6, glm::vec3(1.0f, 1.0f, 1.0f))); //there always needs to be a little bit of a color for it to not appear black

		SceneManager::PrintStats();
	}

	void Sandbox::Update() override
	{
		Camera::UpdateTime();

		PlayerMovement();
	}
	
	void Sandbox::OnEvent(Event& e) override
	{
		//little glitchy but it works for now
		if (e.GetType() == EventType::CursorMoved)
		{
			CursorMovedEvent& c = (CursorMovedEvent&)e;
			Camera::Look(c.GetX(), c.GetY());
		}

		if (e.GetType() == EventType::WindowResize)
		{
			WindowResizeEvent& r = (WindowResizeEvent&)e;
			if (r.GetWidth() != 0 && r.GetHeight() != 0)
			{
				Camera::SetAspectRatio(r.GetWidth(), r.GetHeight());
				Camera::UpdateAspectRatio();
			}
		}
	}

private:
	////Texture defaultTex = Texture("Assets/Textures/default_texture.jpg", 0, HC_IMG_JPG);
	//T/exture skeleton = Texture("Assets/Textures/drawnSkeleton.png", 0, HC_IMG_PNG);
	//Texture dirt = Texture("Assets/Textures/dirtMinecraft.jpg", 0, HC_IMG_JPG);
};

Hercules::Application* Hercules::CreateApplication()
{
	return new Sandbox("Sandbox");
}