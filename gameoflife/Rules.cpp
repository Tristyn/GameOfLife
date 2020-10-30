#include <array>
#include "Rules.h"

namespace Conway
{
	/// <summary>
	/// Returns the state of the neighbors of cell at position. Returns dead cells when the neighbor is out of bounds.
	/// </summary>
	std::array<Cell, 8> Rules::GetCellNeigbors(const Chunk16* chunk, const Vector2Int pos)
	{
		// Moore neighborhood
		std::array<Conway::Cell, 8> array = {};
		array[0] = chunk->CellExists(pos + Vector2Int(-1, -1)) ? chunk->GetCell(pos + Vector2Int(-1, -1)) : Cell::kDead;
		array[1] = chunk->CellExists(pos + Vector2Int(-1, 0)) ? chunk->GetCell(pos + Vector2Int(-1, 0)) : Cell::kDead;
		array[2] = chunk->CellExists(pos + Vector2Int(-1, 1)) ? chunk->GetCell(pos + Vector2Int(-1, 1)) : Cell::kDead;
		array[3] = chunk->CellExists(pos + Vector2Int(0, -1)) ? chunk->GetCell(pos + Vector2Int(0, -1)) : Cell::kDead;
		array[4] = chunk->CellExists(pos + Vector2Int(0, 1)) ? chunk->GetCell(pos + Vector2Int(0, 1)) : Cell::kDead;
		array[5] = chunk->CellExists(pos + Vector2Int(1, -1)) ? chunk->GetCell(pos + Vector2Int(1, -1)) : Cell::kDead;
		array[6] = chunk->CellExists(pos + Vector2Int(1, 0)) ? chunk->GetCell(pos + Vector2Int(1, 0)) : Cell::kDead;
		array[7] = chunk->CellExists(pos + Vector2Int(1, 1)) ? chunk->GetCell(pos + Vector2Int(1, 1)) : Cell::kDead;
		return array;
	}

	/// <summary>
	/// Returns the total alive cells in the array
	/// </summary>
	int Rules::PopulationCount(std::array<Cell, 8> cells)
	{
		// cells would ideally be a Vector or array template, but it works for my uses

		int count = 0;
		for (const Cell cell : cells)
		{
			if (cell == Conway::CellState::kAlive)
			{
				count++;
			}
		}
		return count;
	}

	/// <summary>
	/// Given a cell and it's neighbors, return the next generation of the cell.
	/// </summary>
	Cell Rules::Evolve(const Cell cell, std::array<Cell, 8> neighbors)
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
		// Falling out of this case should not happen
	}

	void Rules::EvolveChunk(Chunk16*& gen0, Chunk16*& gen1)
	{
		for (int x = 0; x < Chunk16::kSizeX; x++)
		{
			for (int y = 0; y < Chunk16::kSizeY; y++)
			{
				Vector2Int pos = Vector2Int(x, y);
				const Cell cell = gen0->GetCell(pos);
				std::array<Cell, 8> neighbors = Rules::GetCellNeigbors(gen0, pos);
				gen1->SetCell(pos, Rules::Evolve(cell, neighbors));
			}
		}
		/// Swap the chunk references, gen0 always stores the latest generation
		std::swap(gen0, gen1);
	}

	/// <summary>
	/// Print the chunks content to stdout
	/// </summary>
	void Rules::Display(const Chunk16* chunk)
	{
		for (int x = 0; x < Chunk16::kSizeX; x++)
		{
			for (int y = 0; y < Chunk16::kSizeY; y++)
			{
				if (chunk->GetCell(Vector2Int(x, y)) == Conway::CellState::kAlive)
				{
					std::cout << "* ";
				}
				else
				{
					std::cout << "  ";
				}
			}
			std::cout << std::endl;
		}
	}
}