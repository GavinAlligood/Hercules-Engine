#include <../Hercules.h>

using namespace Hercules;

//i need to clean up some uses of glm::vec3
//i also need to try and put a draw in application, so the engine handles
//automatically drawing all transforms and meshes
//need to check if component is already on an entity

class Sandbox : public Hercules::Application
{
public:
	Sandbox()
	{
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
			Camera::MoveForward();
		}
		else if (InputManager::IsKeyPressed(HC_KEY_S))
		{
			Camera::MoveBackward();
		}
		if (InputManager::IsKeyPressed(HC_KEY_A))
		{
			Camera::MoveLeft();
		}
		else if (InputManager::IsKeyPressed(HC_KEY_D))
		{
			Camera::MoveRight();
		}
		if (InputManager::IsKeyPressed(HC_KEY_SPACE))
		{
			Camera::MoveUp();
		}
		else if (InputManager::IsKeyPressed(HC_KEY_LEFT_ALT))
		{
			Camera::MoveDown();
		}
	}

	void Sandbox::Start() override
	{
		HC_INFO("Start");
		//					   component id        Entity ID
		SceneManager::AppendComponent(1, DemoComponent(1));
		SceneManager::AppendComponent(2, DemoComponent(2));
		SceneManager::AppendComponent(5, DemoComponent(5));
		SceneManager::AppendComponent(6, TransformComponent(1, glm::vec3(0.0f), glm::vec3(1.0f), glm::vec3(0.0f), defaultTex));
		SceneManager::AppendComponent(7, TransformComponent(2, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f), skeleton));
		SceneManager::AppendComponent(8, TransformComponent(3, glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f), dirt));
		SceneManager::AppendComponent(9, TransformComponent(5, glm::vec3(3.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f), skeleton));

		//Worry about this more later
		HC_STAT("Entity 5:");
		HC_STAT("{0}:{1}:{2}", SceneManager::GetTransformComponent(5)->GetPos().x,
			SceneManager::GetTransformComponent(5)->GetPos().y,
			SceneManager::GetTransformComponent(5)->GetPos().z);

		SceneManager::PrintStats();
	}

	void Sandbox::Update() override
	{
		Camera::UpdateTime();

		PlayerMovement();		
	}
	
	void Sandbox::OnEvent(Event& e)
	{
		if (e.GetType() == EventType::CursorMoved)
		{
			CursorMovedEvent& c = (CursorMovedEvent&)e;
			Camera::Look(c.GetX(), c.GetY());
		}
	}

private:
	Texture defaultTex = Texture("Assets/Textures/default_texture.jpg", 0, HC_IMG_JPG);
	Texture skeleton = Texture("Assets/Textures/drawnSkeleton.png", 0, HC_IMG_PNG);
	Texture dirt = Texture("Assets/Textures/dirtMinecraft.jpg", 0, HC_IMG_JPG);
};

Hercules::Application* Hercules::CreateApplication()
{
	return new Sandbox();
}