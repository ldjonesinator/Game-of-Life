#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

#include "../vendor/imgui/imgui.h"

#include "test_square_batch.h"
#include "../renderer.h"
#include "../vertex_buffer_layout.h"


namespace test {


	TestSquareBatch::TestSquareBatch()
		: m_Proj(glm::ortho(0.0f, 8.0f, 0.0f, 4.5f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_Translation(0, 0, 0)
	{

		m_BatchRender.CreateSquareVertIndices();

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->Bind();
		m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, MAX_VERT * sizeof(Vertex), true);

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		layout.Push<float>(1);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(m_BatchRender.GetIndices(), TILES * INDICES);

		m_Shader = std::make_unique<Shader>("../res/shaders/Basic.shader");
		m_Shader->Bind();

	}

	TestSquareBatch::~TestSquareBatch()
	{
		m_VAO->Unbind();
		m_IndexBuffer->Unbind();
		m_Shader->Unbind();
	}


	void TestSquareBatch::OnUpdate(float deltaTime)
	{
	}

	void TestSquareBatch::OnRender()
	{
		static size_t square_i = 0;

		std::array<Vertex, MAX_VERT> vertices;
		m_BatchRender.CreateBatchRender(vertices.data(), {0.84f, 0.84f, 0.84f, 1.0f});

		if (square_i >= m_BatchRender.GetSquareVertCount()) {
			square_i = 0;
		}

		m_BatchRender.UpdateFullColour(square_i, { 1.0f, 0.2f, 0.4f, 1.0f});

		square_i += VERTICES;


		m_BatchRender.SubData(vertices.size() * sizeof(Vertex), vertices.data());

		glClearColor(0.88f, 0.88f, 0.88f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		glm::mat4 mvp = m_Proj * m_View * model;

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		m_BatchRender.DrawBatchRender();

	}

	void TestSquareBatch::OnImGuiRender()
	{
	    ImGui::SliderFloat2("Translation", &m_Translation.x, -8.0f, 8.0f);

	    ImGui::Text("Application average %.1f ms/frame (%.0f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

}
