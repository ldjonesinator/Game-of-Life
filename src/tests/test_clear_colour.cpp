#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../vendor/imgui/imgui.h"

#include "test_clear_colour.h"

namespace test {

	TestClearColour::TestClearColour()
		: m_ClearColour { 0.88f, 0.88f, 0.88f, 1.0f } {}

	TestClearColour::~TestClearColour() {}

	void TestClearColour::OnUpdate(float deltaTime)
	{
	}

	void TestClearColour::OnRender()
	{
		glClearColor(m_ClearColour[0], m_ClearColour[1], m_ClearColour[2], m_ClearColour[3]);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void TestClearColour::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Colour", m_ClearColour);
	}
}
