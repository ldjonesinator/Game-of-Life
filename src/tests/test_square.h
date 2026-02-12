#pragma once

#include <memory>

#include "test.h"

#include "vertex_array.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"
#include "index_buffer.h"
#include "shader.h"


namespace test {

	class TestSquare : public Test
	{
	public:
		TestSquare();
		~TestSquare();

		void OnUpdate(Timestep ts) override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		glm::mat4 m_Proj, m_View;

		glm::vec3 m_Translation;
	};

}
