#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <functional>

#include "window.h"
#include "timestep.h"


class CameraControl;

#define KEY_LEFT GLFW_KEY_A
#define KEY_RIGHT GLFW_KEY_D
#define KEY_UP GLFW_KEY_W
#define KEY_DOWN GLFW_KEY_S


class Events
{
private:
	double m_MouseX;
	double m_MouseY;
	double m_Scroll = 0;
	Window* m_Window;

//	void (*MousePressFncPtr)(double, double);
public:
	Events();
	~Events();

	void Init(Window* window);
	void EventChecks();
	std::array<double, 2> GetMousePos();
	int MouseDownEvent(std::function<int(double, double, CameraControl&)> MouseFunc, int btn, CameraControl& c_ctrl);
	void MouseScrollEvent(std::function<void(int)>);
	bool KeyDownEvent(std::function<void(bool, int, Timestep)> KeyFunc, int key, int direction, Timestep ts);

private:
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};
