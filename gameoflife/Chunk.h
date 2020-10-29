#pragma once
#include <array>
#include <stdexcept>
#include "Cell.h"
#include "Vector2.h"
namespace Conway
{
	template<size_t _SizeX, size_t _SizeY>
	class Chunk
	{
	public:
		Chunk() = default;

		constexpr const Cell* GetCell(const Vector2Int pos) const
		{
			if (pos.x < 0 || pos.x >= _SizeX)
			{
				return &Cell::dead;
			}
			if (pos.y < 0 || pos.y >= _SizeY)
			{
				return &Cell::dead;
			}
			size_t index = GetIndex(pos);
			return &cells[index];
		}

		constexpr std::array<const Conway::Cell*, 8> GetCellNeigbors(const Vector2Int pos)
		{
			// Moore neighborhood
			std::array<const Conway::Cell*, 8> array = {};
			array[0] = GetCell(pos + Vector2Int(-1, -1));
			array[1] = GetCell(pos + Vector2Int(-1, 0));
			array[2] = GetCell(pos + Vector2Int(-1, 1));
			array[3] = GetCell(pos + Vector2Int(0, -1));
			array[4] = GetCell(pos + Vector2Int(0, 1));
			array[5] = GetCell(pos + Vector2Int(1, -1));
			array[6] = GetCell(pos + Vector2Int(1, 0));
			array[7] = GetCell(pos + Vector2Int(1, 1));
			return array;
		}

		constexpr void SetCell(const Vector2Int pos, const Cell cell)
		{
			size_t index = GetIndex(pos);
			cells[index] = cell;
		}

		constexpr size_t GetIndex(const Vector2Int pos) const
		{
			if (pos.x < 0 || pos.x >= _SizeX)
			{
				throw new std::out_of_range("x out of range");
			}
			if (pos.y < 0 || pos.y >= _SizeY)
			{
				throw new std::out_of_range("y out of range");
			}
			return pos.x + (pos.y * _SizeX);
		}

		static void Iterate(Chunk*& gen0, Chunk*& gen1)
		{
			for (int x = 0; x < _SizeX; x++)
			{
				for (int y = 0; y < _SizeY; y++)
				{
					Vector2Int pos = Vector2Int(x, y);
					const Cell* cell = gen0->GetCell(pos);
					std::array<const Cell*, 8> neighbors = gen0->GetCellNeigbors(pos);
					gen1->SetCell(pos, Cell::Iteration(cell, neighbors));
				}
			}
			std::swap(gen0, gen1);
		}

		static void Display(const Chunk* chunk)
		{
			for (int x = 0; x < _SizeX; x++)
			{
				for (int y = 0; y < _SizeY; y++)
				{
					if (*chunk->GetCell(Vector2Int(x, y)) == Conway::cell_state::kAlive)
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

	private:
		std::array<Cell, _SizeX* _SizeY> cells;
	};

	// Define common types we'll use
	typedef Chunk<16, 16> Chunk16;
}