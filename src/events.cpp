#include "events.h"


Events::Events()
{}

Events::~Events()
{}

void Events::Init(GLFWwindow* window)
{
	m_Window = window;
	glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}


void Events::EventChecks()
{
	glfwGetCursorPos(m_Window, &m_MouseX, &m_MouseY);

}

// returns true if the button is down
bool Events::LeftMouseDownEvent(void (*MousePressFncPtr)(double, double))
{
	int state = glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS) {
		MousePressFncPtr(m_MouseX, m_MouseY);
		return true;
	}
	return false;
}

// returns true if the button is down
bool Events::RightMouseDownEvent(void (*MousePressFncPtr)(double, double))
{
	int state = glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_RIGHT);
	if (state == GLFW_PRESS) {
		MousePressFncPtr(m_MouseX, m_MouseY);
		return true;
	}
	return false;
}
