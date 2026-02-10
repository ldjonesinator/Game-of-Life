#pragma once

#include <stdio.h>

#include <../vendor/glm/glm.hpp>
#include <../vendor/glm/vec3.hpp>
#include <../vendor/glm/vec4.hpp>

#include "batch_render.h"

#define OVERPOP 4
#define UNDERPOP 1
#define POPULATE 3

class Cells
{
private:
	std::array<unsigned int, TILES> m_Cells;
	std::array<unsigned int, TILES> m_EmptyCells;
	std::array<unsigned int, TILES> m_FChangeCells;
	std::array<unsigned int, TILES> m_EChangeCells;
	size_t m_IndexCount;
public:
	Cells();
	~Cells();
	void AddCell(size_t ID);
	void SimulateCells();
	void RenderCells(BatchRender* render);
private:
	bool CheckNeighbour(size_t ID, int x, int y, bool shouldAdd);
	unsigned int CheckNeighbours(size_t ID, bool shouldAdd);
	void RemoveCell(size_t ID);
};
