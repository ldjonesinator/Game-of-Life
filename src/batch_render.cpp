#include "vendor/glm/vec3.hpp"
#include "batch_render.h"
#include "camera_control.h"

BatchRender::BatchRender()
	: m_SquareIndicesFormat{0, 1, 2, 2, 3, 0}
//	4, 5, 6, 6, 7, 4,
{}
BatchRender::~BatchRender()
{}


static Vertex* CreateQuad(Vertex* target, float x, float y, float ID, glm::vec4 colour)
{
	target->position = { x, y, 0.0f };
	target->colour = colour;
	target->ID = ID;
	target++;

	target->position = { x + SQR_SIZE, y, 0.0f };
	target->colour = colour;
	target->ID = ID;
	target++;

	target->position = { x + SQR_SIZE, y + SQR_SIZE, 0.0f };
	target->colour = colour;
	target->ID = ID;
	target++;

	target->position = { x, y + SQR_SIZE, 0.0f };
	target->colour = colour;
	target->ID = ID;
	target++;

	return target;
}

void BatchRender::CreateSquareVertIndices()
{
	unsigned int offset = 0;
	for (size_t i = 0; i < MAX_INDX; i += INDICES) {
		m_SquareIndices[i + 0] = m_SquareIndicesFormat[0] + offset;
		m_SquareIndices[i + 1] = m_SquareIndicesFormat[1] + offset;
		m_SquareIndices[i + 2] = m_SquareIndicesFormat[2] + offset;

		m_SquareIndices[i + 3] = m_SquareIndicesFormat[3] + offset;
		m_SquareIndices[i + 4] = m_SquareIndicesFormat[4] + offset;
		m_SquareIndices[i + 5] = m_SquareIndicesFormat[5] + offset;

		offset += VERTICES;
	}
}

const unsigned int* BatchRender::GetIndices() const {
    return m_SquareIndices.data();
}

void BatchRender::CreateBatchRender(Vertex* vertices_p, glm::vec4 colour)
{
	m_IndexCount = 0;
	m_Buffer = vertices_p;

	for (unsigned int y = 0; y < ROWS; y++) {
		for (unsigned int x = 0; x < COLS; x++) {
			m_Buffer = CreateQuad(m_Buffer, x * (SQR_SIZE + SQR_SPACE), y * (SQR_SIZE + SQR_SPACE),
								(x + y) % 2, colour);
			m_IndexCount += INDICES;
		}
	}
}

unsigned int BatchRender::GetSquareVertCount()
{
	return VERTICES * (m_IndexCount / INDICES);
}

void BatchRender::UpdateFullColour(unsigned int i, glm::vec4 colour)
{
	Vertex* temp_b = m_Buffer - (GetSquareVertCount() - i);
	for (size_t i = 0; i < 4; i ++) {
		temp_b->colour = colour;
		temp_b ++;
	}
}

int BatchRender::GetPositionIndex(double x, double y, CameraControl& c_ctrl)
{
    glm::vec3 cam_pos = c_ctrl.GetCameraPosition();
	glm::vec2 res = c_ctrl.GetResolution();
    float zoom = c_ctrl.GetZoomLevel();
    int size = SQR_SIZE + SQR_SPACE;

    float worldX = ((x - res.x / 2) * zoom) + cam_pos.x;
    float worldY = ((y - res.y / 2) * zoom) + cam_pos.y;

    m_IndexX = (int)(worldX / size);
    m_IndexY = (int)(worldY / size);

    return m_IndexX + m_IndexY * COLS;
}

void BatchRender::SubData(unsigned int size, Vertex* vert_p)
{
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, vert_p);
}

void BatchRender::DrawBatchRender()
{
	glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);
}
