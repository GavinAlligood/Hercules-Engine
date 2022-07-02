#include "ProjectHub/ProjectHub.h"

//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
//}

int main(int argc, char** argv)
{
	std::cout << "Starting" << std::endl;

	ProjectHub* projectHub = new ProjectHub(800, 600);
	projectHub->GlfwInit();
	//glfwSetFramebufferSizeCallback(projectHub->GetWindow(), framebuffer_size_callback);
	//projectHub->ImGuiInit();

	Hercules::Log::Init();
	HC_CORE_INFO("Initialized Log");
	HC_INFO("Welcome to Hercules!");

	//glViewport(0, 0, projectHub->GetWidth(), projectHub->GetHeight());

	while (!glfwWindowShouldClose(projectHub->GetWindow()))
	{
		glfwPollEvents();
		glfwSwapBuffers(projectHub->GetWindow());
	}

	/*Hercules::Editor* editor = new Hercules::Editor("Hercules Editor", "C:/Users/Gavin/source/repos/HerculesEngine/Hercules/DemoProject/", true);
	editor->Run();
	delete editor;*/

	delete projectHub;

	return 0;
}