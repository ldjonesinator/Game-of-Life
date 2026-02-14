#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>
#include <array>
#include <vector>
#include <fstream>
#include <string>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include "vendor/imgui/imgui.h"

#include "GOL.h"
#include "engine/window.h"
#include "engine/renderer.h"


static void GetPresetData(std::vector<std::string>& names, std::vector<size_t>& data)
{
	std::string line;
	std::string value;
	char preset_val = '#';
	char delimiter = ',';
	char ch;

	std::ifstream file("res/presets.txt");
	if (!file) {
		std::cerr << "Unable to open file";
		return;
	}

	bool isFound = false;
	while (std::getline(file, line)) {
		if (isFound) {
			for (size_t i = 0; i < line.length(); i++) {
				ch = line.at(i);
				if (ch == delimiter) {
					data.push_back(static_cast<size_t>(std::stoul(value)));
					value.clear();
				} else {
					value += ch;
				}
			}
			data.push_back(static_cast<size_t>(std::stoul(value))); // final value
			value.clear();
			data.push_back(COLS*ROWS+1); // to indicate the end of the list
			
			isFound = false;
		}
		// finding preset
		if (!line.empty() && line.at(0) == preset_val) {
			names.push_back(line.substr(1));
			isFound = true;
		}

	}
	file.close();
}


GOL::GOL(Window* window)
	: m_Events(std::make_unique<Events>()), m_CameraControl(1.78f),
	m_IO(ImGui::GetIO()), m_MaxFrames(FRAME_UPPER / 4),
	m_CellColour(glm::vec4(1.0f, 0.72f, 0.2f, 1.0f))
{

	m_Window = window;
	m_Events->Init(m_Window);
	m_CameraControl.Init(m_Window);

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

	m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
	m_Shader->Bind();

	GetPresetData(m_PresetNames, m_PresetData);

}

GOL::~GOL()
{
	m_VAO->Unbind();
	m_IndexBuffer->Unbind();
	m_Shader->Unbind();
}


void GOL::ChangeSpeed(int direction, Timestep ts)
{
	m_MaxFrames += m_SpeedChange * direction * ts;
	m_MaxFrames = m_MaxFrames < FRAME_LOWER ? FRAME_LOWER : m_MaxFrames;
	m_MaxFrames = m_MaxFrames > FRAME_UPPER ? FRAME_UPPER : m_MaxFrames;
}

void GOL::OnUpdate(Timestep ts)
{
	static float frame;
	static int index;

	m_CameraControl.WindowResize();

	std::array<Vertex, MAX_VERT> vertices;
	m_BatchRender.CreateBatchRender(vertices.data(), { 0.84f, 0.84f, 0.84f, 1.0f });

	m_Cells.RenderCells(&m_BatchRender, m_CellColour);

	if (m_Events->KeyReleasedEvent(KEY_STEP)) {
		m_NextStep = true;
	}

	if ((frame > 1.0f / m_MaxFrames && !m_ShouldPause) || m_NextStep) {
		m_Cells.SimulateCells();
		m_Iterations ++;
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

	auto speedFunc = [this](int d, Timestep ts)
	{ return ChangeSpeed(d, ts); };

	if (m_GuiInteraction <= 0) {
		index = m_Events->MouseDownEvent(mouseFunc, GLFW_MOUSE_BUTTON_LEFT, m_CameraControl);
		if (index >= 0) {
			m_Cells.AddCell(index);
			m_Cells.UpdateFlaggedCells();
			m_Iterations = 0;
		}
		index = m_Events->MouseDownEvent(mouseFunc, GLFW_MOUSE_BUTTON_RIGHT, m_CameraControl);
		if (index >= 0) {
			m_Cells.RemoveCell(index);
			m_Cells.UpdateFlaggedCells();
			m_Iterations = 0;
		}

		m_Events->KeyDownSpeedEvent(speedFunc, KEY_SPEED_DOWN, ts);
		m_Events->KeyDownSpeedEvent(speedFunc, KEY_SPEED_UP, ts);
		if (m_Events->KeyReleasedEvent(KEY_FULLSCREEN)) {
			m_Window->ToggleFullscreen();
		}
		if (m_Events->KeyReleasedEvent(KEY_PAUSE)) {
			m_ShouldPause = !m_ShouldPause;
		}
		if (m_Events->KeyReleasedEvent(KEY_CLEAR)) {
			m_Cells.ClearCells();
			m_Iterations = 0;
		}
		
	}

	m_CameraControl.CamEvents(m_Events, ts);

	frame += ts;
}

void GOL::OnImGuiRender()
{
	ImGuiIO& io = ImGui::GetIO();
	m_GuiInteraction = io.WantCaptureMouse;
	glm::ivec2 index = m_BatchRender.GetIndexValues();
	ImGui::Text("Iterations: %ld | Populated Cells: %ld", m_Iterations, m_Cells.GetFullCellCount());
	ImGui::Text("Row: %d Column: %d | Index: %d", index.y + 1, index.x + 1, index.x + index.y * COLS);

	ImGui::SliderFloat("Speed", &m_MaxFrames, FRAME_LOWER, FRAME_UPPER);

	if (ImGui::Button("Clear")) {
		m_Cells.ClearCells();
		m_Iterations = 0;
	}
	ImGui::SameLine();
	ImGui::Checkbox("Pause", &m_ShouldPause);
	ImGui::SameLine();
	m_NextStep = ImGui::Button("Next Step");
	ImGui::ColorEdit4("Cell Colour", &m_CellColour.x);

	ImGui::Text("Application average %.1f ms/frame (%.0f FPS)", 1000.0f / io.Framerate, io.Framerate);

	SavedShapes();
}


void GOL::SavedShapes()
{
	size_t start_i = (COLS + ROWS * COLS) / 2;
	ImGui::Text(" ");
	ImGui::Text(" ");
	ImGui::Text("Presets:");
	
	size_t line_length = 0;
	size_t count;
	for (size_t i = 0; i < m_PresetNames.size(); i++) {
		line_length += m_PresetNames[i].length();
		
		if (ImGui::Button(m_PresetNames[i].c_str())) {
			m_Iterations = 0;
			m_CameraControl.CentreCamera();
			count = 0;
			for (size_t value : m_PresetData) {
				if (value == COLS*ROWS+1) {
					count ++;
				} else if (count == i) {
					m_Cells.AddCell(start_i + value);
					
				} else if (count > i) {
					break;
				}
			}
			m_Cells.UpdateFlaggedCells();
		}

		if (line_length < 34) {
			ImGui::SameLine();
		} else {
			line_length = 0;
		}
	}
	
	ImGui::SameLine();
}
