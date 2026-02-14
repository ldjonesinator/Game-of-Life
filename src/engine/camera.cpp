#include "camera.h"

Camera::Camera(float left, float right, float bottom, float top)
	: m_ProjMat(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMat(1.0f)
{
	m_ViewProjMat = m_ProjMat * m_ViewMat;
}

Camera::~Camera()
{}


void Camera::SetProjMat(float left, float right, float bottom, float top)
{
	m_ProjMat = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	m_ViewProjMat = m_ProjMat * m_ViewMat;
}

void Camera::ReCalcViewMatrix()
{
	// multiply with identity matrix
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);

	m_ViewMat = glm::inverse(transform);
	m_ViewProjMat = m_ProjMat * m_ViewMat;
}
