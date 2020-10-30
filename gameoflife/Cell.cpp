#include <array>
#include "Cell.h"
namespace Conway
{
	const Cell Cell::alive = Cell(CellState::kAlive);
	const Cell Cell::dead = Cell(CellState::kDead);

	Cell::Cell(Conway::CellState aCellState) : m_value(aCellState) { }

	Cell::operator const Conway::CellState() const
	{
		return m_value;
	}
};