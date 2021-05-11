#include <../Hercules.h>

using namespace Hercules;

class Sandbox : public Hercules::Application
{
public:
	Sandbox() {};
	~Sandbox() {};

	void Move()
	{
		//HC_INFO("Update");
		if (InputManager::IsKeyPressed(HC_KEY_A))
		{
			HC_TRACE("Moved Left!");
		}
		else if (InputManager::IsKeyPressed(HC_KEY_D))
		{
			HC_TRACE("Moved Right!");
		}
		else if (InputManager::IsKeyPressed(HC_KEY_S))
		{
			HC_TRACE("Moved Down!");
		}
		else if (InputManager::IsKeyPressed(HC_KEY_W))
		{
			HC_TRACE("Moved Up!");
		}
	}

	void Sandbox::Update()
	{
		Move();
	}

	void Sandbox::Start()
	{
		HC_INFO("Start");
	}
};

//a little confusing, but i get how this works
Hercules::Application* Hercules::CreateApplication()
{
	return new Sandbox();
}