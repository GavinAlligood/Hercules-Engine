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

		if (InputManager::IsKeyPressed(HC_KEY_UP))
		{
			float x = SceneManager::GetTransformComponent(2)->GetPos().x;
			float y = SceneManager::GetTransformComponent(2)->GetPos().y;
			float z = SceneManager::GetTransformComponent(2)->GetPos().z;
			SceneManager::GetTransformComponent(2)->SetPos(glm::vec3(x, y += 0.1f, z));
		}
		if (InputManager::IsKeyPressed(HC_KEY_DOWN))
		{
			float x = SceneManager::GetTransformComponent(2)->GetPos().x;
			float y = SceneManager::GetTransformComponent(2)->GetPos().y;
			float z = SceneManager::GetTransformComponent(2)->GetPos().z;
			SceneManager::GetTransformComponent(2)->SetPos(glm::vec3(x, y -= 0.1f, z));
		}
		if (InputManager::IsKeyPressed(HC_KEY_LEFT))
		{
			float x = SceneManager::GetTransformComponent(2)->GetPos().x;
			float y = SceneManager::GetTransformComponent(2)->GetPos().y;
			float z = SceneManager::GetTransformComponent(2)->GetPos().z;
			SceneManager::GetTransformComponent(2)->SetPos(glm::vec3(x -= 0.1f, y, z));
		}
		if (InputManager::IsKeyPressed(HC_KEY_RIGHT))
		{
			float x = SceneManager::GetTransformComponent(2)->GetPos().x;
			float y = SceneManager::GetTransformComponent(2)->GetPos().y;
			float z = SceneManager::GetTransformComponent(2)->GetPos().z;
			SceneManager::GetTransformComponent(2)->SetPos(glm::vec3(x += 0.1f, y, z));
		}
		if (InputManager::IsKeyPressed(HC_KEY_V))
		{
			float x = SceneManager::GetTransformComponent(2)->GetPos().x;
			float y = SceneManager::GetTransformComponent(2)->GetPos().y;
			float z = SceneManager::GetTransformComponent(2)->GetPos().z;
			SceneManager::GetTransformComponent(2)->SetPos(glm::vec3(x, y, z += 0.1f));
		}
		if (InputManager::IsKeyPressed(HC_KEY_B))
		{
			float x = SceneManager::GetTransformComponent(2)->GetPos().x;
			float y = SceneManager::GetTransformComponent(2)->GetPos().y;
			float z = SceneManager::GetTransformComponent(2)->GetPos().z;
			SceneManager::GetTransformComponent(2)->SetPos(glm::vec3(x, y, z -= 0.1f));
		}
	}

	void Sandbox::Start() override
	{
		HC_INFO("Start");
		//					   component id        Entity ID
		SceneManager::AppendComponent(1, DemoComponent(1));
		SceneManager::AppendComponent(2, DemoComponent(2));
		SceneManager::AppendComponent(5, DemoComponent(5));
		SceneManager::AppendComponent(6, TransformComponent(1, glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f), dirt, glm::vec4(HC_COLOR_WHITE)));
		SceneManager::AppendComponent(7, TransformComponent(2, glm::vec3(-1.0f, 1.0f, 0.5f), glm::vec3(0.5f), glm::vec3(0.0f), dirt, glm::vec4(HC_COLOR_GREEN)));
		SceneManager::AppendComponent(8, TransformComponent(3, glm::vec3(2.0f, 0.5f, 0.0f), glm::vec3(1.0f), glm::vec3(25.0f, 45.0f, 0.0f), dirt, glm::vec4(HC_COLOR_WHITE)));
		SceneManager::AppendComponent(9, TransformComponent(5, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(45.0f, 0.0f, 0.0f), defaultTex, glm::vec4(HC_COLOR_WHITE)));
		SceneManager::AppendComponent(4, TransformComponent(6, glm::vec3(-1.2f, 1.0f, -6.0f), glm::vec3(1.0f), glm::vec3(0.0f), defaultTex, glm::vec4(HC_COLOR_WHITE)));
		SceneManager::AppendComponent(3, LightComponent(6, glm::vec3(1.0f, 1.0f, 1.0f))); //there always needs to be a little bit of a color for it to not appear black

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