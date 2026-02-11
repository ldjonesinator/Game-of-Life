#include "events.h"


Events::Events()
{}

Events::~Events()
{}

void Events::Init(Window* window)
{
	m_Window = window;
	glfwSetInputMode(m_Window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}


void Events::EventChecks()
{
	glfwGetCursorPos(m_Window->GetWindow(), &m_MouseX, &m_MouseY);

}

// returns true if the button is down
int Events::LeftMouseDownEvent(int (*MousePressFncPtr)(double, double, int, int))
{
	std::array<int, 2> win_size = m_Window->GetCurrentSize();
	int state = glfwGetMouseButton(m_Window->GetWindow(), GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS) {
		// inverts the mouseY origin
		return MousePressFncPtr(m_MouseX, win_size[1] - m_MouseY, win_size[0], win_size[1]);
	}
	return -2; // -2 means mouse was not pressed
}

// returns the event output
int Events::RightMouseDownEvent(int (*MousePressFncPtr)(double, double, int, int))
{
	std::array<int, 2> win_size = m_Window->GetCurrentSize();
	int state = glfwGetMouseButton(m_Window->GetWindow(), GLFW_MOUSE_BUTTON_RIGHT);
	if (state == GLFW_PRESS) {
		// inverts the mouseY origin
		return MousePressFncPtr(m_MouseX, win_size[1] - m_MouseY, win_size[0], win_size[1]);
	}
	return -2; // -2 means mouse was not pressed
}
