#pragma once

#ifdef HC_PLATFORM_WINDOWS

extern Hercules::Application* Hercules::CreateApplication();

int main(int argc, char** argv)
{
	Hercules::Log::Init();
	HC_CORE_INFO("Initialized Log");
	HC_INFO("Welcome to Hercules!");
	
	auto app = Hercules::CreateApplication();
	app->Run();
	delete app;
}

#endif // HC_PLATFORM_WINDOWS
