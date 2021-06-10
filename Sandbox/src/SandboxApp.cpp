#include <../Hercules.h>

using namespace Hercules;

//i need to clean up some uses of glm::vec3

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

	//Maybe make a render function required by Application.cpp
	void Draw()
	{
		std::map<unsigned int, TransformComponent>::iterator it;
		for (it = SceneManager::GetTransformComponentList().begin();
			it != SceneManager::GetTransformComponentList().end(); ++it)
		{
			SpatialRenderer::DrawCube(skeleton,
				glm::vec3((*it).second.GetPos()),
				glm::vec3(1.0f),
				glm::vec3(0.0f),
				glm::vec4(HC_COLOR_WHITE),
				SCENE_CAMERA, shader);
		}
	}

	void Sandbox::Start() override
	{
		HC_INFO("Start");
		//					   component id        Entity ID
		SceneManager::AppendComponent(1, DemoComponent(1));
		SceneManager::AppendComponent(2, DemoComponent(2));
		SceneManager::AppendComponent(3, DemoComponent(1));
		SceneManager::AppendComponent(4, DemoComponent(2));
		SceneManager::AppendComponent(5, DemoComponent(5));
		SceneManager::AppendComponent(6, TransformComponent(1, glm::vec3(0.0f)));
		SceneManager::AppendComponent(7, TransformComponent(2, glm::vec3(1.0f, 0.0f, 0.0f)));
		SceneManager::AppendComponent(8, TransformComponent(3, glm::vec3(2.0f, 0.0f, 0.0f)));
		SceneManager::AppendComponent(9, TransformComponent(5, glm::vec3(3.0f, 0.0f, 0.0f)));
		
		SceneManager::PrintStats();
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