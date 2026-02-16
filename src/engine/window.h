#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <array>

#define WINDOWED_SCALE 1.5f

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
	/** @param VSync: set true when you want the monitor's refresh rate */
	Window(bool VSync);
	~Window();
	void InitialiseWindow(float scale, bool VSync);

	bool IsValid() const { return m_isValid; };

	GLFWwindow* GetWindow() const { return m_Window; }
	std::array<int, 2> GetCurrentSize();
	std::array<int, 2> GetMinSize() { return std::array<int, 2>{m_WinWidth, m_WinHeight}; }

	void ToggleFullscreen();
};
