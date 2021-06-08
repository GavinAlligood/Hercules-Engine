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
		for (float i = 0.0; i < 7.0; i++)
		{
			SpatialRenderer::DrawCube(defaultTex,
				glm::vec3(0.0f, i, 0.0f),
				glm::vec3(1.0f),
				glm::vec3(0.0f),
				glm::vec4(HC_COLOR_WHITE),
				SCENE_CAMERA, shader);
		}

		for (float i = 1.0f; i < 3.0f; i++)
		{
			SpatialRenderer::DrawCube(defaultTex,
				glm::vec3(i, 5.0f, 0.0f),
				glm::vec3(1.0f),
				glm::vec3(0.0f),
				glm::vec4(HC_COLOR_WHITE),
				SCENE_CAMERA, shader);
		}

		for (float i = 1.0f; i < 3.0f; i++)
		{
			SpatialRenderer::DrawCube(defaultTex,
				glm::vec3(-i, 5.0f, 0.0f),
				glm::vec3(1.0f),
				glm::vec3(0.0f),
				glm::vec4(HC_COLOR_WHITE),
				SCENE_CAMERA, shader);
		}

	}

	void Sandbox::Start() override
	{
		HC_INFO("Start");
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
			HC_TRACE("{0}:{1}", c.GetX(), c.GetY());
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