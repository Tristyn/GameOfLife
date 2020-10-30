#include <array>
#include "Cell.h"
namespace Conway
{
	const Cell Cell::kAlive = Cell(CellState::kAlive);
	const Cell Cell::kDead = Cell(CellState::kDead);

	// Implicit conversion between Cell and CellState
	Cell::Cell(Conway::CellState aCellState) : m_value(aCellState) { }
	Cell::operator const Conway::CellState() const
	{
		return m_value;
	}
};