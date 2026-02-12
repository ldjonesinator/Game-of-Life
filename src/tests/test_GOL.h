#pragma once

#include <memory>

#include "test.h"

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "index_buffer.h"
#include "shader.h"
#include "batch_render.h"
#include "cells.h"
#include "events.h"
#include "camera.h"
#include "camera_control.h"


#define FRAME_LOWER 0.0f
#define FRAME_UPPER 50.0f


namespace test {

	class TestGOL : public Test
	{
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		Window* m_Window;
		std::unique_ptr<Events> m_Events;

		CameraControl m_CameraControl;

		ImGuiIO& m_IO;

		float m_MaxFrames;
		bool m_ShouldPause = true;
		bool m_NextStep = false;

		BatchRender m_BatchRender;
		Cells m_Cells;
		glm::vec4 m_CellColour;

	public:
		TestGOL(Window* window);
		~TestGOL();

		void OnUpdate(Timestep ts) override;

		void OnImGuiRender() override;

	private:
		int GetPositionIndex(double x, double y, int x_res, int y_res);
		void MoveCamera(bool isHorz, int direction, Timestep ts);
	};
}
