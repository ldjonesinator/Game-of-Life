#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <array>

#include "engine/window.h"
#include "engine/debug.h"


Window::Window(bool VSync)
{
	InitialiseWindow(WINDOWED_SCALE, VSync);
}

Window::~Window()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::InitialiseWindow(float scale, bool VSync)
{
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);


	m_Monitor = glfwGetPrimaryMonitor();
	m_Mode = glfwGetVideoMode(m_Monitor);

	m_WinWidth = m_Mode->width / scale;
	m_WinHeight = m_Mode->height / scale;

	m_Window = glfwCreateWindow(m_WinWidth, m_WinHeight, "John Conway's Game of Life", NULL, NULL);

	if (m_Window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwGetWindowPos(m_Window, &m_xPos, &m_yPos);

	glfwMakeContextCurrent(m_Window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	GLDebugSetup();

	std::cout << "\nVersion: " << glGetString(GL_VERSION) << "\n" << std::endl;
	glViewport(0, 0, m_WinWidth, m_WinHeight);

	// VSync is 1
	glfwSwapInterval(0);
	glfwSwapBuffers(m_Window);


	m_isValid = true;
}


std::array<int, 2> Window::GetCurrentSize()
{
	glfwGetFramebufferSize(m_Window, &m_CurWidth, &m_CurHeight);
	return std::array<int, 2>{m_CurWidth, m_CurHeight};
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::ToggleFullscreen()
{
	static bool isWindowed = true;
	if (isWindowed) {
		glfwSetWindowMonitor(m_Window, m_Monitor, 0, 0, m_Mode->width, m_Mode->height, m_Mode->refreshRate);
	} else {
		glfwSetWindowMonitor(m_Window, NULL, m_xPos, m_yPos, m_WinWidth, m_WinHeight, m_Mode->refreshRate);
	}
	isWindowed = !(isWindowed);
	glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);
}
