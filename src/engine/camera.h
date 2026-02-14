#pragma once

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/vec3.hpp"

class Camera
{
private:
	glm::mat4 m_ProjMat;
	glm::mat4 m_ViewMat;
	glm::mat4 m_ViewProjMat;

	glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f};
public:
	Camera(float left, float right, float bottom, float top);
	~Camera();

	void SetProjMat(float left, float right, float bottom, float top);

	const glm::vec3& GetPosition() const { return m_Position; }
	void SetPosition(const glm::vec3& position) { m_Position = position; ReCalcViewMatrix(); }

	const glm::mat4& GetProjMatrix() const { return m_ProjMat; }
	const glm::mat4& GetViewMatrix() const { return m_ViewMat; }
	const glm::mat4& GetViewProjMatrix() const { return m_ViewProjMat; }
private:
	void ReCalcViewMatrix();
};
