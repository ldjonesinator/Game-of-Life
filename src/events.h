#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Events
{
private:
	double m_MouseX;
	double m_MouseY;
	GLFWwindow* m_Window;

//	void (*MousePressFncPtr)(double, double);
public:
	Events();
	~Events();

	void Init(GLFWwindow* window);
	void EventChecks();
	bool LeftMouseDownEvent(void (*MousePressFncPtr)(double, double));
	bool RightMouseDownEvent(void (*MousePressFncPtr)(double, double));
};
