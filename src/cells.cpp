#include <iostream>

#include "cells.h"

#include "batch_render.h"

Cells::Cells()
	: m_IndexCount(0)
{
	for (size_t i = 0; i < TILES; i ++) {
		m_Cells[i] = 0;
		m_EmptyCells[i] = 0;
		m_FlaggedCells[i] = false;
	}
}

Cells::~Cells()
{}

// returns true if the neighbour is on the other side of the screen
static bool isOnOppositeEdge(int id, int nbour_id)
{
	if (id % COLS == 0) { // left edge
		if (nbour_id % COLS == COLS - 1) {
			return true;
		}
	} else if (id % COLS == COLS - 1) { // right edge
		if (nbour_id % COLS == 0) {
			return true;
		}
	}
	return false;
}

bool Cells::CheckNeighbour(size_t ID, int x, int y)
{
    int base = static_cast<int>(ID);
    int nbour_id = base + x + (y * COLS);

    if (!isOnOppositeEdge(base, nbour_id) && nbour_id >= 0 &&
    	nbour_id < static_cast<int>(TILES) && static_cast<size_t>(nbour_id) != ID)
    {
        m_FlaggedCells[nbour_id] = true;
        if (m_Cells[nbour_id] != 0) {
            return true;
        }
    }
    return false;
}


unsigned int Cells::CheckNeighbours(size_t ID)
{
	unsigned int count = 0;
	for (int x = -1; x < 2; x++) {
		for (int y = -1; y < 2; y++) {
			if (x == 0 && y == 0) continue;

			if (CheckNeighbour(ID, x, y)) {
				count ++;
			}
		}
	}
	m_FlaggedCells[ID] = true;
	return count;
}


void Cells::AddCell(size_t ID)
{
	if (ID < TILES) {
		CheckNeighbours(ID);
		m_EmptyCells[ID] = 0;
		m_Cells[ID] = 1;
		m_IndexCount ++;
	} else {
		std::cout << "Cell index: " << ID << " out of range" << std::endl;
	}
}

void Cells::RemoveCell(size_t ID)
{
	if (ID < TILES) {
        CheckNeighbours(ID);
        m_Cells[ID] = 0;
        m_EmptyCells[ID] = 0;
        m_IndexCount --;
    } else {
		std::cout << "Cell index: " << ID << " out of range" << std::endl;
	}
}

void Cells::UpdateFlaggedCells()
{
	for (size_t i = 0; i < TILES; i ++) {
		if (m_FlaggedCells[i]) {
			if (m_Cells[i] != 0) {
				m_Cells[i] = CheckNeighbours(i) + 1;
			} else {
				m_EmptyCells[i] = CheckNeighbours(i);
			}
		}
		m_FlaggedCells[i] = false;
	}
}

void Cells::SimulateCells()
{
	// remember that m_Cells contains the count of neighbours + 1 (itself)
	for (size_t i = 0; i < TILES; i ++) {
		if (m_EmptyCells[i] == POPULATE) {
			AddCell(i);
		} else if (m_Cells[i] >= 1 && (m_Cells[i] >= (OVERPOP + 1) || m_Cells[i] <= (UNDERPOP + 1)) ) {
			RemoveCell(i);
		}
	}

	UpdateFlaggedCells();
}

void Cells::RenderCells(BatchRender* render, glm::vec4 colour)
{
	for (size_t i = 0; i < TILES; i ++) {
		if (m_Cells[i] != 0) {
			render->UpdateFullColour(i * VERTICES, colour);
		}
	}
}

size_t Cells::GetFullCellCount() const
{
	return m_IndexCount;
}
