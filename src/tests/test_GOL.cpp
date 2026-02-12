#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>
#include <array>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include "vendor/imgui/imgui.h"

#include "test_GOL.h"
#include "window.h"
#include "renderer.h"
#include "vertex_buffer_layout.h"




namespace test {


	TestGOL::TestGOL(Window* window)
		: m_Events(std::make_unique<Events>()), m_CameraControl(1.78f),
		m_IO(ImGui::GetIO()), m_MaxFrames(FRAME_UPPER / 4),
		m_CellColour(glm::vec4(1.0f, 0.72f, 0.2f, 1.0f))
	{

		m_Window = window;
		m_Events->Init(m_Window);
		m_CameraControl.Init(m_Window);

		m_BatchRender.CreateSquareVertIndices();

//		m_Cells.AddCell(410);
//		m_Cells.AddCell(450);
//		m_Cells.AddCell(490);
//		m_Cells.AddCell(530);
//		m_Cells.AddCell(411);
//		m_Cells.AddCell(453);
//		m_Cells.AddCell(489);
//		m_Cells.AddCell(531);
//		m_Cells.AddCell(412);
//		m_Cells.AddCell(452);
//		m_Cells.AddCell(529);
//		m_Cells.AddCell(532);
//		m_Cells.UpdateFlaggedCells();

		m_VAO = std::make_unique<VertexArray>();
		m_VAO->Bind();
		m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, MAX_VERT * sizeof(Vertex), true);

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		layout.Push<float>(1);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(m_BatchRender.GetIndices(), TILES * INDICES);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();

	}

	TestGOL::~TestGOL()
	{
		m_VAO->Unbind();
		m_IndexBuffer->Unbind();
		m_Shader->Unbind();
	}


	void TestGOL::OnUpdate(Timestep ts)
	{
		static float frame;
		static int index;

		m_CameraControl.WindowResize();

		// std::array<int, 2> win_size = m_Window->GetCurrentSize();
		// m_UprBoundX = (float)(win_size[0]);
		// m_UprBoundY = (float)(win_size[1]);
		// m_Camera.SetProjMat(m_UprBoundX * m_LwrBndMult, m_UprBoundX, m_UprBoundY * m_LwrBndMult, m_UprBoundY);
		// m_Camera.SetPosition(m_CameraPosition);

		std::array<Vertex, MAX_VERT> vertices;
		m_BatchRender.CreateBatchRender(vertices.data(), { 0.84f, 0.84f, 0.84f, 1.0f });

		m_Cells.RenderCells(&m_BatchRender, m_CellColour);

		if ((frame > 1.0f / m_MaxFrames && !m_ShouldPause) || m_NextStep) {
			m_Cells.SimulateCells();
			frame = 0.0f;
		}

		m_BatchRender.SubData(vertices.size() * sizeof(Vertex), vertices.data());

		glClearColor(0.88f, 0.88f, 0.88f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		// glm::mat4 mvp = m_Camera.GetViewProjMatrix() * model;

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", m_CameraControl.GetCamera().GetViewProjMatrix());

		m_BatchRender.DrawBatchRender();

		m_Events->EventChecks();

		auto mouseFunc = [this](double x, double y, CameraControl& cc)
		{ return m_BatchRender.GetPositionIndex(x, y, cc); };

		index = m_Events->MouseDownEvent(mouseFunc, GLFW_MOUSE_BUTTON_LEFT, m_CameraControl);
		if (index >= 0) {
			m_Cells.AddCell(index);
			m_Cells.UpdateFlaggedCells();
		}
		index = m_Events->MouseDownEvent(mouseFunc, GLFW_MOUSE_BUTTON_RIGHT, m_CameraControl);
		if (index >= 0) {
			m_Cells.RemoveCell(index);
			m_Cells.UpdateFlaggedCells();
		}

		m_CameraControl.CamEvents(m_Events, ts);

		frame += ts;
	}

	void TestGOL::OnImGuiRender()
	{
	    ImGui::Text("Full Cell Count: %ld", m_Cells.GetFullCellCount());

//	    ImGui::SliderFloat2("Translation", &m_Translation.x, -1600.0f, 0);
	    ImGui::SliderFloat("Speed", &m_MaxFrames, FRAME_LOWER, FRAME_UPPER);

	    ImGui::Checkbox("Pause", &m_ShouldPause);
	    ImGui::SameLine();
	    m_NextStep = ImGui::Button("Next Step");
	    ImGui::ColorEdit4("Cell Colour", &m_CellColour.x);

	    ImGui::Text("Application average %.1f ms/frame (%.0f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	}

}
