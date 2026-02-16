#pragma once

#include <array>

#include "engine/vertex_buffer_layout.h"
#include "grid_config.h"


class CameraControl;


class BatchRender
{
private:
	std::array<unsigned int, INDICES> m_SquareIndicesFormat;
	std::array<unsigned int, MAX_INDX> m_SquareIndices;
	unsigned int m_IndexCount;
	Vertex* m_Buffer;

	int m_IndexX = 0;
	int m_IndexY = 0;

public:
	BatchRender();
	~BatchRender();

	void CreateSquareVertIndices();
	const unsigned int* GetIndices() const { return m_SquareIndices.data(); }
	void CreateBatchRender(Vertex* vertices_p, glm::vec4 colour);

	unsigned int GetSquareVertCount() { return VERTICES * (m_IndexCount / INDICES); }
	void UpdateFullColour(unsigned int i, glm::vec4 colour);
	int GetPositionIndex(double x, double y, CameraControl& c_ctrl);
	glm::ivec2 GetIndexValues() { return {m_IndexX, m_IndexY}; }

	void SubData(unsigned int size, Vertex* vert_p) { glBufferSubData(GL_ARRAY_BUFFER, 0, size, vert_p); }
	void DrawBatchRender() { glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr); }

};
