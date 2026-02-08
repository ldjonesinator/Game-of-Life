#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

#include "../vendor/imgui/imgui.h"

#include "test_square.h"
#include "../renderer.h"


namespace test {

	TestSquare::TestSquare()
		: m_Proj(glm::ortho(0.0f, 8.0f, 0.0f, 4.5f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_Translation(1, 1, 0)
	{
		float positions[] = {
			-0.5f, -0.5f, 0.0f, 0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
			0.5f, -0.5f, 0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			0.5f, 0.5f, 0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
			-0.5f, 0.5f, 0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 8 * 4 * sizeof(float), false);

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		layout.Push<float>(1);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer  = std::make_unique<IndexBuffer>(indices, 6);

		m_Shader = std::make_unique<Shader>("../res/shaders/Basic.shader");
		m_Shader->Bind();

	}

	TestSquare::~TestSquare() {}

	void TestSquare::OnUpdate(float deltaTime)
	{
	}

	void TestSquare::OnRender()
	{
		static float r = 0.0f;
		static float increment = 0.01f;

		glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		Renderer renderer;


		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		glm::mat4 mvp = m_Proj * m_View * model;

	    m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);

	    if (r > 1.0f) {
	        increment = -0.01f;
	    } else if (r < 0.0f) {
	        increment = 0.01f;
	    }
	    r += increment;

		renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
	}

	void TestSquare::OnImGuiRender()
	{
		static bool show_fullscreen_window = false;

//	    ImGui::Begin("View");

	    ImGui::SliderFloat2("Translation", &m_Translation.x, 0.0f, 8.0f);
	    ImGui::Checkbox("Fullscreen", &show_fullscreen_window);

	    ImGui::Text("Application average %.1f ms/frame (%.0f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//	    ImGui::End();
	}
}
