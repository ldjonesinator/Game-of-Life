#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"


class Events
{
private:
	double m_MouseX;
	double m_MouseY;
	Window* m_Window;

//	void (*MousePressFncPtr)(double, double);
public:
	Events();
	~Events();

	void Init(Window* window);
	void EventChecks();
	int LeftMouseDownEvent(int (*MousePressFncPtr)(double, double, int, int));
	int RightMouseDownEvent(int (*MousePressFncPtr)(double, double, int, int));
};
