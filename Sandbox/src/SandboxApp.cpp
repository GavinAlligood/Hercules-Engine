#include <../Hercules.h>

using namespace Hercules;

class Sandbox : public Hercules::Application
{
public:
	Sandbox() {};
	~Sandbox() {};

	void Sandbox::Update()
	{
	}

	void Sandbox::Start()
	{
		HC_INFO("Start");
	}
private:
	
};

Hercules::Application* Hercules::CreateApplication()
{
	return new Sandbox();
}