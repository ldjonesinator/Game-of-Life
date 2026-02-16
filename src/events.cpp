#include "events.h"

#include <iostream>
#include <vector>


Events::Events()
{}

Events::~Events()
{}

void Events::Init(Window* window)
{
	m_Window = window;
	GLFWwindow* win = m_Window->GetWindow();
	glfwSetWindowUserPointer(win, this);
}


void Events::EventChecks()
{
	glfwGetCursorPos(m_Window->GetWindow(), &m_MouseX, &m_MouseY);
	m_MouseY = m_Window->GetCurrentSize()[1] - m_MouseY;

}

// returns true if the button is down
int Events::MouseDownEvent(std::function<int(double, double, CameraControl&)> MouseFunc, int btn, CameraControl& c_ctrl)
{
	int state = glfwGetMouseButton(m_Window->GetWindow(), btn);
	if (state == GLFW_PRESS) {
		// inverts the mouseY origin
		return MouseFunc(m_MouseX, m_MouseY, c_ctrl);
	}
	return -2; // -2 means mouse was not pressed
}

void Events::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Events* events = static_cast<Events*>(glfwGetWindowUserPointer(window));

    if (events)
        events->m_Scroll = yoffset;
}

void Events::MouseScrollEvent(std::function<void(int)> ScrollFunc)
{
	glfwSetScrollCallback(m_Window->GetWindow(), scroll_callback);
	ScrollFunc(m_Scroll);
	m_Scroll = 0;
}

bool Events::KeyDownCamEvent(std::function<void(bool, int, Timestep)> KeyFunc, int key, int direction, Timestep ts)
{
	if (glfwGetKey(m_Window->GetWindow(), key) == GLFW_PRESS) {
		KeyFunc(key == KEY_LEFT || key == KEY_RIGHT, direction, ts);
		return true;
	}
	return false;
}

bool Events::KeyDownSpeedEvent(std::function<void(int, Timestep)> KeyFunc, int key, Timestep ts)
{
	if (glfwGetKey(m_Window->GetWindow(), key) == GLFW_PRESS) {
		KeyFunc((key == KEY_SPEED_UP) * 2 - 1, ts);
		return true;
	}
	return false;
}

bool Events::KeyReleasedEvent(int key)
{
	static std::vector<int> pressed_keys;
	std::vector<int>::iterator it = std::find(pressed_keys.begin(), pressed_keys.end(), key);
	
	if (glfwGetKey(m_Window->GetWindow(), key) == GLFW_PRESS) {
		if (it == pressed_keys.end()) {
			pressed_keys.push_back(key);
		}
	} else if (it != pressed_keys.end()) {
		pressed_keys.erase(it);
		return true;
	}
	return false;
	
};
