#include <../Hercules.h>

using namespace Hercules;

class Sandbox : public Hercules::Application
{
public:
	Sandbox() {};
	~Sandbox() {};

	void Move()
	{
		if (InputManager::IsKeyPressed(HC_KEY_W))
		{
			HC_TRACE("Moved Up!");
		}
		else if (InputManager::IsKeyPressed(HC_KEY_A))
		{
			HC_TRACE("Moved Left!");
		}
		else if (InputManager::IsKeyPressed(HC_KEY_S))
		{
			HC_TRACE("Moved Down!");
		}
		else if (InputManager::IsKeyPressed(HC_KEY_D))
		{
			HC_TRACE("Moved Right!");
		}
	}

	void Character()
	{
		if (InputManager::IsMousePressed(HC_MOUSE_BUTTON_1))
		{
			HC_TRACE("Attacked!");
		}
		else if (InputManager::IsMousePressed(HC_MOUSE_BUTTON_2))
		{
			HC_TRACE("Collected Item!");
		}
	}

	void Sandbox::Update()
	{
		//Move();
		//Character();
		//auto [x, y] = InputManager::GetMousePos();
		//HC_TRACE("{0}, {1}", x, y);
	}

	void Sandbox::Start()
	{
		HC_INFO("Start");
		//Renderer::Draw(HC_2D_SQUARE);
		//Later will be:
		//HC_CREATE(HC_2D_SQUARE);
	}
private:
	
};

//a little confusing, but i get how this works
Hercules::Application* Hercules::CreateApplication()
{
	return new Sandbox();
}