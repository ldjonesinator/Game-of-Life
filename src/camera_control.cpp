#include <cstdlib>
#include <iostream>
#include <cmath>

#include "camera_control.h"


CameraControl::CameraControl(float m_AspectRatio)
	: m_Camera(-m_AspectRatio * m_ZoomLevel / 2, m_AspectRatio * m_ZoomLevel / 2, -m_ZoomLevel, m_ZoomLevel)
{}

CameraControl::~CameraControl()
{}

float CameraControl::GetAspectRatio()
{
	std::array<int, 2> win_size = m_Window->GetCurrentSize();
    m_ResX = (float)(win_size[0]);
    m_ResY = (float)(win_size[1]);
	m_AspectRatio = win_size[0] / win_size[1];
	return m_AspectRatio;
}

void CameraControl::Init(Window* window)
{
	m_Window = window;
	GetAspectRatio();
}

void CameraControl::CheckCameraBounds()
{
	float minX = (m_ResX * m_ZoomLevel / 2);
	float minY = (m_ResY * m_ZoomLevel / 2);
	float maxX = WORLD_X - (m_ResX * m_ZoomLevel / 2);
	float maxY = WORLD_Y - (m_ResY * m_ZoomLevel / 2);

	m_CameraPosition.x = (m_CameraPosition.x < minX) ? minX : m_CameraPosition.x;
	m_CameraPosition.x = (m_CameraPosition.x > maxX) ? maxX : m_CameraPosition.x;
	m_CameraPosition.y = (m_CameraPosition.y < minY) ? minY : m_CameraPosition.y;
	m_CameraPosition.y = (m_CameraPosition.y > maxY) ? maxY : m_CameraPosition.y;
}

void CameraControl::WindowResize()
{
	GetAspectRatio();

	float size_x = m_ResX * m_ZoomLevel / 2;
	float size_y = m_ResY * m_ZoomLevel / 2;
	m_Camera.SetProjMat(-size_x, size_x, -size_y, size_y);

	CheckCameraBounds();
	m_Camera.SetPosition(m_CameraPosition);
}

void CameraControl::MoveCamera(bool isHorz, int direction, Timestep ts)
	{
		if (isHorz) {
			m_CameraPosition.x += m_CameraSpeed * ts * direction * m_ZoomLevel;
		} else {
			m_CameraPosition.y += m_CameraSpeed * ts * direction * m_ZoomLevel;
		}
	}

void CameraControl::ZoomCamera(int zoomLevel)
{
	double mouseX, mouseY;

	m_ZoomLevel -= m_ZoomSpeed * zoomLevel;
	if (m_ZoomLevel < MAX_ZOOM) {
		m_ZoomLevel = MAX_ZOOM;
	} else if (m_ZoomLevel > MIN_ZOOM) {
		m_ZoomLevel = MIN_ZOOM;
	} else {
		glfwGetCursorPos(m_Window->GetWindow(), &mouseX, &mouseY);
		m_CameraPosition.x += (mouseX - m_ResX / 2) * (int)((zoomLevel + 1) / 2) * m_ZoomLevel;
		m_CameraPosition.y -= (mouseY - m_ResY / 2) * (int)((zoomLevel + 1) / 2) * m_ZoomLevel;
	}

	WindowResize();
}

void CameraControl::CamEvents(std::unique_ptr<Events>& events, Timestep ts)
{
	auto key_func = [this](bool h, int d, Timestep ts)
		{ return MoveCamera(h, d, ts); };

	auto scroll_func = [this](int zl)
		{ return ZoomCamera(zl); };

	events->KeyDownEvent(key_func, KEY_LEFT, -1, ts);
	events->KeyDownEvent(key_func, KEY_RIGHT, 1, ts);
	events->KeyDownEvent(key_func, KEY_DOWN, -1, ts);
	events->KeyDownEvent(key_func, KEY_UP, 1, ts);

	events->MouseScrollEvent(scroll_func);
}