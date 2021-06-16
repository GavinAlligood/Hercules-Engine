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
	}

	~Sandbox()
	{
		SpatialRenderer::End();
		glfwTerminate();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
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

		if (InputManager::IsMousePressed(HC_MOUSE_BUTTON_2))
		{	
			holdingRight = true;
		}
		else
		{
			holdingRight = false;
		}
	}

	void Sandbox::Start() override
	{
		HC_INFO("Start");
		//					   component id        Entity ID
		SceneManager::AppendComponent(1, DemoComponent(1));
		SceneManager::AppendComponent(2, DemoComponent(2));
		SceneManager::AppendComponent(5, DemoComponent(5));
		SceneManager::AppendComponent(6, TransformComponent(1, glm::vec3(4.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(0.0f), dirt, glm::vec4(HC_COLOR_WHITE)));
		SceneManager::AppendComponent(7, TransformComponent(2, glm::vec3(-1.0f, 1.0f, 0.5f), glm::vec3(0.5f), glm::vec3(0.0f), dirt, glm::vec4(HC_COLOR_GREEN)));
		SceneManager::AppendComponent(8, TransformComponent(3, glm::vec3(2.0f, 0.5f, 0.0f), glm::vec3(1.0f), glm::vec3(25.0f, 45.0f, 0.0f), dirt, glm::vec4(HC_COLOR_WHITE)));
		SceneManager::AppendComponent(9, TransformComponent(5, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f), glm::vec3(45.0f, 0.0f, 0.0f), defaultTex, glm::vec4(HC_COLOR_WHITE)));
		SceneManager::AppendComponent(4, TransformComponent(6, glm::vec3(-1.2f, 1.0f, -6.0f), glm::vec3(1.0f), glm::vec3(0.0f), defaultTex, glm::vec4(HC_COLOR_WHITE)));
		SceneManager::AppendComponent(3, LightComponent(6, glm::vec3(1.0f, 1.0f, 1.0f))); //there always needs to be a little bit of a color for it to not appear black

		SceneManager::PrintStats();
	}

	void Sandbox::Update() override
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		Camera::UpdateTime();

		PlayerMovement();
	}
	
	void Sandbox::OnEvent(Event& e)
	{
		//little glitchy but it works for now
		if (e.GetType() == EventType::CursorMoved && holdingRight)
		{
			CursorMovedEvent& c = (CursorMovedEvent&)e;
			Camera::Look(centerX + c.GetX(), centerY + c.GetY());
		}
	}

	void Sandbox::ImGuiRender()
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
			static float iVx;
			static float iVy;
			static float iVz;
			static float x = SceneManager::GetTransformComponent(6)->GetPos().x;
			static float y = SceneManager::GetTransformComponent(6)->GetPos().y;
			static float z = SceneManager::GetTransformComponent(6)->GetPos().z;

			ImGui::Begin("Editor");

			ImGui::DragFloat("X", &iVx, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::DragFloat("Y", &iVy, 0.1f, 0.0f, 0.0f, "%.2f");
			ImGui::DragFloat("Z", &iVz, 0.1f, 0.0f, 0.0f, "%.2f");

			SceneManager::GetTransformComponent(6)->SetPos(glm::vec3(x + iVx, y + iVy, z + iVz));
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

private:
	Texture defaultTex = Texture("Assets/Textures/default_texture.jpg", 0, HC_IMG_JPG);
	Texture skeleton = Texture("Assets/Textures/drawnSkeleton.png", 0, HC_IMG_PNG);
	Texture dirt = Texture("Assets/Textures/dirtMinecraft.jpg", 0, HC_IMG_JPG);

	bool polygon = false;
	bool point = false;
	bool holdingRight = false;
	float centerX = 480, centerY = 270;

	//imgui testing
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
};

Hercules::Application* Hercules::CreateApplication()
{
	return new Sandbox();
}