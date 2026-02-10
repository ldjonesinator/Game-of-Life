#include <iostream>

#include "cells.h"

#include "batch_render.h"

Cells::Cells()
	: m_IndexCount(0)
{
	for (size_t i = 0; i < TILES; i ++) {
		m_Cells[i] = 0;
		m_EmptyCells[i] = 0;
		m_FChangeCells[i] = 0;
		m_EChangeCells[i] = 0;
	}
}

Cells::~Cells()
{}


// increases or decreases neighbour count for every neighbouring cell even if they are empty
bool Cells::CheckNeighbour(size_t ID, int x, int y, bool shouldSubtrct)
{
	int nbour_id = ID + x + (y * COLS);
	if ((unsigned int)nbour_id == ID) {
		return false;
	}
	if (nbour_id < TILES && nbour_id >= 0) { // out of bounds
		if (m_EChangeCells[nbour_id] != 0) {
			m_EChangeCells[nbour_id] += 1 - (2 * shouldSubtrct);
			std::cout << "Full: " << m_EChangeCells[nbour_id] << std::endl;
			return true;
		} else {
			m_EChangeCells[nbour_id] += 1 - (2 * shouldSubtrct);
			std::cout << "Empty: " << m_EChangeCells[nbour_id] << std::endl;

		}
	}
	return false;
}


unsigned int Cells::CheckNeighbours(size_t ID, bool shouldSubtrct)
{
	unsigned int count = 0;
	for (int x = -1; x < 2; x++) {
		for (int y = -1; y < 2; y++) {
			if (CheckNeighbour(ID, x, y, shouldSubtrct)) {
				count ++;
			}
		}
	}
	return count;
}


void Cells::AddCell(size_t ID)
{
	if (ID < TILES) {
		m_EChangeCells[ID] = 0;
		m_FChangeCells[ID] = 1 + CheckNeighbours(ID, false);
		m_IndexCount ++;
	} else {
		std::cout << "Cell index: " << ID << " out of range" << std::endl;
	}
}

void Cells::RemoveCell(size_t ID)
{
	m_FChangeCells[ID] = 0;
	m_EChangeCells[ID] += CheckNeighbours(ID, true);
}

void Cells::SimulateCells()
{
	// remember that m_Cells contains the count of neighbours + 1 (itself)
	for (size_t i = 0; i < TILES; i ++) {
		if (m_EmptyCells[i] >= POPULATE) {
			std::cout << "ADD: " << m_EChangeCells[i] << std::endl;
			AddCell(i);
		} else if (m_Cells[i] >= 1 && (m_Cells[i] >= (OVERPOP + 1) || m_Cells[i] <= (UNDERPOP + 1)) ) {
			std::cout << "REMOVE:" << std::endl;
			std::cout << (m_Cells[i] >= (OVERPOP + 1)) << std::endl;
			RemoveCell(i);
		}
	}
}

void Cells::RenderCells(BatchRender* render)
{
	for (size_t i = 0; i < TILES; i ++) {
		m_Cells[i] += m_FChangeCells[i];
		m_EmptyCells[i] += m_EChangeCells[i];
		m_FChangeCells[i] = 0;
		m_EChangeCells[i] = 0;
	}

	for (size_t i = 0; i < TILES; i ++) {
		if (m_Cells[i] != 0) {
			render->UpdateFullColour(i * VERTICES, { 1.0f, 0.2f, 0.4f, 1.0f });
		}
	}
}
