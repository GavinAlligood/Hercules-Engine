#include <../Hercules.h>

using namespace Hercules;

class Sandbox : public Hercules::Application
{
public:
	Sandbox()
	{
		SpatialRenderer::Init();
		Camera::Init(5.0f);

		shader = new Shader("Assets/Shaders/Vertex.shader",
			"Assets/Shaders/Fragment.shader");
	}

	~Sandbox()
	{
		SpatialRenderer::End();
		delete shader;
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

	void Draw()
	{
		for (int i = 0; i < SceneManager::GetDemoComponents().size(); i++)
		{
			if (i == 0)
			{
				SpatialRenderer::DrawCube(defaultTex,
					glm::vec3(0.0f, 0.0f, 0.0f),
					glm::vec3(1.0f),
					glm::vec3(0.0f),
					glm::vec4(HC_COLOR_RED),
					SCENE_CAMERA, shader);
			}
			else if (i == 1)
			{
				SpatialRenderer::DrawCube(defaultTex,
					glm::vec3(1.0f, 0.0f, 0.0f),
					glm::vec3(1.0f),
					glm::vec3(0.0f),
					glm::vec4(HC_COLOR_GREEN),
					SCENE_CAMERA, shader);
			}
			else
			{
				SpatialRenderer::DrawCube(defaultTex,
					glm::vec3(2.0f, 0.0f, 0.0f),
					glm::vec3(1.0f),
					glm::vec3(0.0f),
					glm::vec4(HC_COLOR_BLUE),
					SCENE_CAMERA, shader);
			}
			
		}
	}

	void Sandbox::Start() override
	{
		HC_INFO("Start");
		SceneManager::AppendComponent(1, DemoComponent(1));
		SceneManager::AppendComponent(2, DemoComponent(2));
		SceneManager::AppendComponent(3, DemoComponent(1));
		SceneManager::AppendComponent(4, DemoComponent(2));
		SceneManager::AppendComponent(5, DemoComponent(5));
		if (SceneManager::GetMeshComponent(5))
		{
			HC_TRACE("Selected entity");
		}
		else
		{
			HC_TRACE("Entity does not exist");
		}
	}

	void Sandbox::Update() override
	{
		Camera::UpdateTime();

		PlayerMovement();
		Draw();
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

	Shader* shader = nullptr;
};

Hercules::Application* Hercules::CreateApplication()
{
	return new Sandbox();
}