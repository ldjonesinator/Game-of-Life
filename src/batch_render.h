#pragma once

#include <array>

#include "vertex_buffer_layout.h"

#define ROWS 67
#define COLS 117
#define TILES (ROWS * COLS)

#define INDICES 6
#define VERTICES 4

#define MAX_VERT (TILES * VERTICES)
#define MAX_INDX (TILES * INDICES)

#define SQR_SIZE 20
#define SQR_SPACE 2

class BatchRender
{
private:
	std::array<unsigned int, INDICES> m_SquareIndicesFormat;
	std::array<unsigned int, MAX_INDX> m_SquareIndices;
	unsigned int m_IndexCount;
	Vertex* m_Buffer;

public:
	BatchRender();
	~BatchRender();

	void CreateSquareVertIndices();
	const unsigned int* GetIndices() const;
	void CreateBatchRender(Vertex* vertices_p, glm::vec4 colour);

	unsigned int GetSquareVertCount();
	void UpdateFullColour(unsigned int i, glm::vec4 colour);

	void SubData(unsigned int size, Vertex* vert_p);
	void DrawBatchRender();


};
