#include <../Hercules.h>

using namespace Hercules;

class Sandbox : public Hercules::Application
{
public:
	Sandbox()
	{
	}

	~Sandbox()
	{
	}

	void Sandbox::Start() override
	{
		HC_INFO("Start");
	}

	void Sandbox::Update() override
	{
		
	}
	

private:
	//Texture defaultTex = Texture("Assets/Textures/default_texture.jpg", 0, HC_IMG_JPG);
};

Hercules::Application* Hercules::CreateApplication()
{
	return new Sandbox();
}