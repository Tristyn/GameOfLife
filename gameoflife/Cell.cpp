#include <array>
#include "Cell.h"
namespace Conway
{
	const Cell Cell::alive = Cell(cell_state::kAlive);
	const Cell Cell::dead = Cell(cell_state::kDead);

	Cell::Cell() = default;

	const Cell Cell::Iteration(const Cell* cell, const std::array<const Cell*, 8> neighbors)
	{
		size_t populationCount = Cell::PopulationCount(neighbors);
		switch ((*cell))
		{
		case Conway::cell_state::kDead:
			//Births: Each dead cell adjacent to exactly three live neighbors will become live in the next generation.
			if (populationCount == 3)
			{
				return Cell(Conway::cell_state::kAlive);
			}
			break;
		case Conway::cell_state::kAlive:
			//Death by isolation: Each live cell with one or fewer live neighbors will die in the next generation.
			if (populationCount <= 1)
			{
				return Cell(Conway::cell_state::kDead);
			}
			//Death by overcrowding: Each live cell with four or more live neighbors will die in the next generation.
			else if (populationCount >= 4)
			{
				return Cell(Conway::cell_state::kDead);
			}
			//Survival: Each live cell with either two or three live neighbors will remain alive for the next generation.
			else
			{
				return Cell(Conway::cell_state::kAlive);
			}
			break;
		}
		return Cell(Conway::cell_state::kDead);
	}
};