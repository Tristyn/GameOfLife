#include <array>
#include "Rules.h"

namespace Conway
{
	template<size_t _Size>
	int Rules::PopulationCount(std::array<Cell, _Size>  cells)
	{
		int count = 0;
		for (const Cell cell : cells)
		{
			switch (cell)
			{
			case Conway::CellState::kAlive:
				count++;
				break;
			}
		}
		return count;
	}

	Cell Rules::Iteration(const Cell cell, std::array<Cell, 8> neighbors)
	{
		size_t populationCount = Rules::PopulationCount(neighbors);
		switch (cell)
		{
		case Conway::CellState::kDead:
			//Births: Each dead cell adjacent to exactly three live neighbors will become live in the next generation.
			if (populationCount == 3)
			{
				return Cell(Conway::CellState::kAlive);
			}
			else
			{
				return Cell(Conway::CellState::kDead);
			}
			break;
		case Conway::CellState::kAlive:
			//Death by isolation: Each live cell with one or fewer live neighbors will die in the next generation.
			if (populationCount <= 1)
			{
				return Cell(Conway::CellState::kDead);
			}
			//Death by overcrowding: Each live cell with four or more live neighbors will die in the next generation.
			else if (populationCount >= 4)
			{
				return Cell(Conway::CellState::kDead);
			}
			//Survival: Each live cell with either two or three live neighbors will remain alive for the next generation.
			else
			{
				return Cell(Conway::CellState::kAlive);
			}
			break;
		}
		return Cell(Conway::CellState::kDead);
	}
}