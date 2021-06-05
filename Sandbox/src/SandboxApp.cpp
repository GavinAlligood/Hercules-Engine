#include <../Hercules.h>

using namespace Hercules;

class Sandbox : public Hercules::Application
{
public:
	Sandbox() {}
	~Sandbox() {}

	void Sandbox::Update() override
	{
	}

	void Sandbox::Start() override
	{
		HC_INFO("Start");
	}
};

Hercules::Application* Hercules::CreateApplication()
{
	return new Sandbox();
}