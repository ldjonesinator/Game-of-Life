#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

#include "../vendor/imgui/imgui.h"

#include "test_GOL.h"
#include "../renderer.h"
#include "../vertex_buffer_layout.h"


namespace test {


	TestGOL::TestGOL()
		: m_Proj(glm::ortho(0.0f, 8.0f, 0.0f, 4.5f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_Translation(0, 0, 0), m_MaxFrames(1000)
	{

		m_BatchRender.CreateSquareVertIndices();

//		m_Cells.AddCell(300);
//		m_Cells.AddCell(340);
//		m_Cells.AddCell(260);
//		m_Cells.AddCell(341);
//		m_Cells.AddCell(259);

		m_Cells.AddCell(410);
		m_Cells.AddCell(450);
		m_Cells.AddCell(490);
		m_Cells.AddCell(530);
		m_Cells.AddCell(411);
		m_Cells.AddCell(453);
		m_Cells.AddCell(489);
		m_Cells.AddCell(531);
		m_Cells.AddCell(412);
		m_Cells.AddCell(452);
		m_Cells.AddCell(529);
		m_Cells.AddCell(532);

		m_Cells.UpdateFlaggedCells();

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

	TestGOL::~TestGOL() {}


	void TestGOL::OnUpdate(float deltaTime)
	{
	}

	void TestGOL::OnRender()
	{
		static float frame = 0.0f;

		std::array<Vertex, MAX_VERT> vertices;
		m_BatchRender.CreateBatchRender(vertices.data(), {0.84f, 0.84f, 0.84f, 1.0f});

		m_Cells.RenderCells(&m_BatchRender);

		if (frame > m_MaxFrames) {
			std::cout << "\nSTART\n" << std::endl;
			m_Cells.SimulateCells();
			frame = 0.0f;
		}

		m_BatchRender.SubData(vertices.size() * sizeof(Vertex), vertices.data());

		glClearColor(0.88f, 0.88f, 0.88f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		glm::mat4 mvp = m_Proj * m_View * model;

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		m_BatchRender.DrawBatchRender();

		frame ++;

	}

	void TestGOL::OnImGuiRender()
	{
		static bool show_fullscreen_window = false;

//	    ImGui::Begin("View");

	    ImGui::SliderFloat2("Translation", &m_Translation.x, -8.0f, 8.0f);
	    ImGui::SliderFloat("Speed", &m_MaxFrames, 20.0f, 1000.0f);
	    ImGui::Checkbox("Fullscreen", &show_fullscreen_window);

	    ImGui::Text("Application average %.1f ms/frame (%.0f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//	    ImGui::End();
	}

}
