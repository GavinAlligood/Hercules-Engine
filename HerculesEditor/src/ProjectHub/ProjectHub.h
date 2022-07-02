#pragma once

#include "../Editor/HerculesEditor.h"

class ProjectHub {
public:
	ProjectHub(int width, int height) : m_Width(width), m_Height(height) {}
	~ProjectHub();

	void GlfwInit();

	void ImGuiInit();

	void ImGuiRender();

	inline int GetWidth() { return m_Width; }
	inline int GetHeight() { return m_Height; }

	inline GLFWwindow* GetWindow() { return m_Window; }
private:
	int m_Width, m_Height;

	GLFWwindow* m_Window = NULL;
};