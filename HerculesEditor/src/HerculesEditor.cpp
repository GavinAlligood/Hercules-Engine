#include <../Hercules.h>

namespace Hercules {

	class Editor : public Application {
	public:
		Editor()
		{

		}

		~Editor()
		{
			glfwTerminate();
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}

		void Editor::Start() override
		{

		}

		void Editor::Update() override
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
		}

		void Editor::OnEvent(Event& e)
		{
		}

		void Editor::ImGuiRender()
		{
			ImGui::ShowDemoWindow();

			//Performance
			{
				static float f = 0.0f;
				static int counter = 0;

				ImGui::Begin("Performance");

				ImGui::Text("FPS: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::End();
			}

			{
				//static float iVx;
				//static float iVy;
				//static float iVz;
				//static float x = SceneManager::GetTransformComponent(6)->GetPos().x;
				//static float y = SceneManager::GetTransformComponent(6)->GetPos().y;
				//static float z = SceneManager::GetTransformComponent(6)->GetPos().z;

				ImGui::Begin("Editor");

				//ImGui::DragFloat("X", &iVx, 0.1f, 0.0f, 0.0f, "%.2f");
				//ImGui::DragFloat("Y", &iVy, 0.1f, 0.0f, 0.0f, "%.2f");
				//ImGui::DragFloat("Z", &iVz, 0.1f, 0.0f, 0.0f, "%.2f");

				//SceneManager::GetTransformComponent(6)->SetPos(glm::vec3(x + iVx, y + iVy, z + iVz));
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}
	private:
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	};

	Application* CreateApplication()
	{
		return new Editor();
	}
}