#pragma once

#include <memory>

#include "test.h"

#include "../vertex_array.h"
#include "../vertex_buffer.h"
#include "../vertex_buffer_layout.h"
#include "../index_buffer.h"
#include "../shader.h"
#include "../batch_render.h"


namespace test {

	class TestSquareBatch : public Test
	{
	public:
		TestSquareBatch();
		~TestSquareBatch();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;

	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		glm::mat4 m_Proj, m_View;

		glm::vec3 m_Translation;

		BatchRender m_BatchRender;
	};

}
