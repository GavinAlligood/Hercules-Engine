#include <../Hercules.h>

using namespace Hercules;

class Editor : public Hercules::Application
{
public:
	Editor()
	{
		SpatialRenderer::Init();
		Camera::Init(5.0f);
	}

	~Editor()
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

	void Editor::Start() override
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

	void Editor::Update() override
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		Camera::UpdateTime();

		PlayerMovement();
	}

	void Editor::OnEvent(Event& e)
	{
		//little glitchy but it works for now
		if (e.GetType() == EventType::CursorMoved && holdingRight)
		{
			CursorMovedEvent& c = (CursorMovedEvent&)e;
			Camera::Look(centerX + c.GetX(), centerY + c.GetY());
		}
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


		ImGuiIO& io = ImGui::GetIO(); (void)io;
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void Editor::ImGuiInit()
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplGlfw_InitForOpenGL(Editor::GetWindow().GetWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");
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
	return new Editor();
}