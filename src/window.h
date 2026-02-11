#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	bool m_isValid = false;
	GLFWmonitor* m_Monitor;
	const GLFWvidmode* m_Mode;
	GLFWwindow* m_Window;

	int m_WinWidth, m_WinHeight;
	int m_CurWidth, m_CurHeight;
	int m_xPos, m_yPos;

public:
	Window(float scale);
	~Window();
	void InitialiseWindow(float scale);
	bool IsValid() const;
	GLFWwindow* GetWindow() const;
	std::array<int, 2> GetCurrentSize();
	void ToggleFullscreen();
};
