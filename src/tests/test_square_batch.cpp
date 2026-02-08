#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stdlib.h>

#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"

#include "../vendor/imgui/imgui.h"

#include "test_square_batch.h"
#include "../renderer.h"
#include "../vertex_buffer_layout.h"

GLuint m_QuadVA, m_QuadVB, m_QuadIB;

const unsigned int ROWS = 8;
const unsigned int COLS = 5;
const unsigned int TILES = ROWS * COLS;
const unsigned int INDICES = 6;
const unsigned int MAX_VERT = TILES * 4;
const unsigned int MAX_INDX = TILES * INDICES;

namespace test {

	static void CreateSquareVertIndices(unsigned int* indices, const unsigned int indices_format[])
	{
		std::vector<unsigned int> v_indices;
		for (size_t i = 0; i < TILES; i ++) {
			for (size_t j = 0; j < INDICES; j ++) {
				v_indices.push_back(indices_format[j] + 4 * i);
			}
		}

		std::copy(v_indices.begin(), v_indices.end(), indices);
	}

	TestSquareBatch::TestSquareBatch()
		: m_Proj(glm::ortho(0.0f, 8.0f, 0.0f, 4.5f, -1.0f, 1.0f)),
		m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
		m_Translation(3, 2, 0)
	{


		const unsigned int indices_format[INDICES] = {
			0, 1, 2, 2, 3, 0,
//			4, 5, 6, 6, 7, 4,
		};
		unsigned int indices[MAX_INDX];
		CreateSquareVertIndices(indices, indices_format);

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(nullptr, MAX_VERT * TILES * sizeof(float), false);

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(4);
		layout.Push<float>(1);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, TILES * INDICES);

		m_Shader = std::make_unique<Shader>("../res/shaders/Basic.shader");
		m_Shader->Bind();


	}

	TestSquareBatch::~TestSquareBatch() {}

	static Vertex* CreateQuad(Vertex* target, float x, float y, float size, float ID)
	{
		target->position = { x, y, 0.0f };
		target->colour = { 0.18f, 0.6f, 0.96f, 1.0f };
		target->ID = ID;
		target++;

		target->position = { x + size, y, 0.0f };
		target->colour = { 0.18f, 0.6f, 0.96f, 1.0f };
		target->ID = ID;
		target++;

		target->position = { x + size, y + size, 0.0f };
		target->colour = { 0.18f, 0.6f, 0.96f, 1.0f };
		target->ID = ID;
		target++;

		target->position = { x, y + size, 0.0f };
		target->colour = { 0.18f, 0.6f, 0.96f, 1.0f };
		target->ID = ID;
		target++;

		return target;
	}

	static void UpdateFullColour(Vertex* target, unsigned int count, unsigned int i, Vec4 colour)
	{
		target -= (count - i);
		for (size_t i = 0; i < 4; i ++) {
			target->colour = colour;
			target ++;
		}
	}

	void TestSquareBatch::OnUpdate(float deltaTime)
	{
	}

	void TestSquareBatch::OnRender()
	{
		static size_t square_i = 0;

		size_t indexCount = 0;
		std::array<Vertex, MAX_VERT> vertices;
		Vertex* buffer = vertices.data();
		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 8; x++) {
				buffer = CreateQuad(buffer, x, y, 0.98f, (x + y) % 2);
				indexCount += INDICES;
			}
		}

		UpdateFullColour(buffer, (4 * indexCount / INDICES), square_i, { 1.0f, 0.2f, 0.4f, 1.0f});

		square_i += 4;
		if (square_i >= 4 * indexCount / INDICES) {
			square_i = 0;
		}

		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Translation);
		glm::mat4 mvp = m_Proj * m_View * model;

	    m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", mvp);

		m_VAO->Bind();
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

	}

	void TestSquareBatch::OnImGuiRender()
	{
		static bool show_fullscreen_window = false;

//	    ImGui::Begin("View");

	    ImGui::SliderFloat2("Translation", &m_Translation.x, 0.0f, 8.0f);
	    ImGui::Checkbox("Fullscreen", &show_fullscreen_window);

	    ImGui::Text("Application average %.1f ms/frame (%.0f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//	    ImGui::End();
	}
}
