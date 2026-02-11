#pragma once

#include <memory>

#include "test.h"

#include "../vertex_array.h"
#include "../vertex_buffer.h"
#include "../vertex_buffer_layout.h"
#include "../index_buffer.h"
#include "../shader.h"
#include "../batch_render.h"
#include "../cells.h"
#include "../events.h"


#define FRAME_LOWER 10.0f
#define FRAME_UPPER 500.0f


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

		glm::mat4 m_Proj, m_View;

		glm::vec3 m_Translation;

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

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}
