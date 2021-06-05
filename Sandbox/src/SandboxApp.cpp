#include <../Hercules.h>

using namespace Hercules;

class Sandbox : public Hercules::Application
{
public:
	Sandbox()
	{
		spatialRenderer = new SpatialRenderer();
		sceneCamera = new Camera(3.0f);
	}

	~Sandbox()
	{
		delete spatialRenderer;
		delete sceneCamera;
	}

	void Player()
	{
		if (InputManager::IsKeyPressed(HC_KEY_W))
		{
			sceneCamera->MoveForward();
		}
		else if (InputManager::IsKeyPressed(HC_KEY_S))
		{
			sceneCamera->MoveBackward();
		}
		if (InputManager::IsKeyPressed(HC_KEY_A))
		{
			sceneCamera->MoveLeft();
		}
		else if (InputManager::IsKeyPressed(HC_KEY_D))
		{
			sceneCamera->MoveRight();
		}
		if (InputManager::IsKeyPressed(HC_KEY_SPACE))
		{
			sceneCamera->MoveUp();
		}
		else if (InputManager::IsKeyPressed(HC_KEY_LEFT_ALT))
		{
			sceneCamera->MoveDown();
		}

		//work on this later
		/*if (InputManager::IsKeyPressed(HC_KEY_ESCAPE))
		{
			glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			InScene = false;
		}
		else if (InputManager::IsMousePressed(HC_MOUSE_BUTTON_1))
		{
			glfwSetInputMode(window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			InScene = true;
		}*/
	}

	void DrawLevel()
	{
		for (int i = 0; i < 4; i++)
		{

			spatialRenderer->DrawCube(dirt,
				glm::vec3(x + minecraftX, y, z - 5.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec4(HC_COLOR_WHITE),
				SCENE_CAMERA);
			minecraftX += 0.5;
		}
		minecraftX = 0;

		for (int i = 0; i < 4; i++)
		{

			spatialRenderer->DrawCube(dirt,
				glm::vec3(x + minecraftX, y, z - 4.5f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec4(HC_COLOR_WHITE),
				SCENE_CAMERA);
			minecraftX += 0.5;
		}
		minecraftX = 0;

		for (int i = 0; i < 4; i++)
		{

			spatialRenderer->DrawCube(dirt,
				glm::vec3(x + minecraftX, y, z - 4.0f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec4(HC_COLOR_WHITE),
				SCENE_CAMERA);
			minecraftX += 0.5;
		}
		minecraftX = 0;

		for (int i = 0; i < 4; i++)
		{

			spatialRenderer->DrawCube(dirt,
				glm::vec3(x + minecraftX, y, z - 3.5f),
				glm::vec3(0.5f, 0.5f, 0.5f),
				glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec4(HC_COLOR_WHITE),
				SCENE_CAMERA);
			minecraftX += 0.5;
		}
		minecraftX = 0;
	}

	void Sandbox::Start() override
	{
		HC_INFO("Start");
	}

	void Sandbox::Update() override
	{
		sceneCamera->UpdateTime();

		DrawLevel();
		Player();
	}
	
	void Sandbox::OnEvent(Event& e)
	{
		if (e.GetType() == EventType::CursorMoved)
		{
			CursorMovedEvent& c = (CursorMovedEvent&)e;
			sceneCamera->Look(c.GetX(), c.GetY());
		}
	}

private:
	SpatialRenderer* spatialRenderer = nullptr;
	
	Camera* sceneCamera = nullptr;

	Texture dirt = Texture("Assets/Textures/dirtMinecraft.jpg", 0, HC_IMG_JPG);

	float minecraftX = 0;

	float x = 0.1f;
	float y = 0.0f;
	float z = -3.0f;
};

Hercules::Application* Hercules::CreateApplication()
{
	return new Sandbox();
}