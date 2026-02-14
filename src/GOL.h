#pragma once

#include <memory>

#include "vendor/imgui/imgui.h"

#include "engine/vertex_array.h"
#include "engine/vertex_buffer.h"
#include "engine/vertex_buffer_layout.h"
#include "engine/index_buffer.h"
#include "engine/shader.h"
#include "engine/batch_render.h"
#include "cells.h"
#include "events.h"
#include "engine/camera.h"
#include "engine/camera_control.h"


#define FRAME_LOWER 0.0f
#define FRAME_UPPER 50.0f


class GOL
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
	bool m_GuiInteraction = false;

	float m_MaxFrames;
	int m_SpeedChange = 50;

	bool m_ShouldPause = true;
	bool m_NextStep = false;
	size_t m_Iterations = 0;

	BatchRender m_BatchRender;
	Cells m_Cells;
	glm::vec4 m_CellColour;

	std::vector<size_t> m_PresetData;
	std::vector<std::string> m_PresetNames;

public:
	GOL(Window* window);
	~GOL();

	void OnUpdate(Timestep ts);
	void OnImGuiRender();

private:
	void SavedShapes();
	void ChangeSpeed(int direction, Timestep ts);
};

