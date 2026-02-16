#include <iostream>

#include "cells.h"

#include "engine/batch_render.h"


Cells::Cells()
	: m_IndexCount(0)
{
	ClearCells();
}

Cells::~Cells()
{}

/** Resets every cell so they have no neighbours and none are flagged  */
void Cells::ClearCells()
{
	for (size_t i = 0; i < TILES; i ++) {
		m_Cells[i] = 0;
		m_EmptyCells[i] = 0;
		m_FlaggedCells[i] = false;
	}
	m_IndexCount = 0;
}


/**
 * @return true if the neighbour cell is on the other side of the screen (horizontally)
 */
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

/**
 * @return true of that cell is populated
 */
bool Cells::CheckNeighbour(size_t ID, int x, int y, bool shouldFlag)
{
    int base = static_cast<int>(ID);
    int nbour_id = base + x + (y * COLS);

    if (!isOnOppositeEdge(base, nbour_id) && nbour_id >= 0 &&
    	nbour_id < static_cast<int>(TILES) && static_cast<size_t>(nbour_id) != ID)
    {
        m_FlaggedCells[nbour_id] = shouldFlag ? true : m_FlaggedCells[nbour_id];
        if (m_Cells[nbour_id] != 0) {
            return true;
        }
    }
    return false;
}

/** Checks all 8 cells around to see if any are populated
 * @return how many populated neighbouring cells there are
 * @param shouldFlag false if you don't want to change the flagged state of neighbours
 */
unsigned int Cells::CheckNeighbours(size_t ID, bool shouldFlag)
{
	unsigned int count = 0;
	for (int x = -1; x < 2; x++) {
		for (int y = -1; y < 2; y++) {
			if (x == 0 && y == 0) continue;

			if (CheckNeighbour(ID, x, y, shouldFlag)) {
				count ++;
			}
		}
	}
	m_FlaggedCells[ID] = shouldFlag ? true : m_FlaggedCells[ID];
	return count;
}

/** Adds a populated cell and flags it and its neighbours */
void Cells::AddCell(size_t ID)
{
	if (ID < TILES) {
		if (m_Cells[ID] == 0) {
			CheckNeighbours(ID, true);
			m_EmptyCells[ID] = 0;
			m_Cells[ID] = 1;
			m_IndexCount ++;
		}
	} else {
		std::cout << "Cell index: " << ID << " out of range" << std::endl;
	}
}

/** Removes a populated cell and flags it and its neighbouring cells */
void Cells::RemoveCell(size_t ID)
{
	if (ID < TILES) {
		if (m_Cells[ID] != 0) {
		    CheckNeighbours(ID, true);
		    m_Cells[ID] = 0;
		    m_EmptyCells[ID] = 0;
		    m_IndexCount --;
		}
    } else {
		std::cout << "Cell index: " << ID << " out of range" << std::endl;
	}
}

/** Updates the correct neighbour count of each flagged cell */
void Cells::UpdateFlaggedCells()
{
	for (size_t i = 0; i < TILES; i ++) {
		if (m_FlaggedCells[i]) {
			if (m_Cells[i] != 0) {
				m_Cells[i] = CheckNeighbours(i, false) + 1;
			} else {
				m_EmptyCells[i] = CheckNeighbours(i, false);
			}
		}
		m_FlaggedCells[i] = false;
	}
}

/** Applies the rules of the game of life */
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

/** Updates the colour of the populated cells */
void Cells::RenderCells(BatchRender* render, glm::vec4 colour)
{
	for (size_t i = 0; i < TILES; i ++) {
		if (m_Cells[i] != 0) {
			render->UpdateFullColour(i * VERTICES, colour);
		}
	}
}
