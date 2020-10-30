#ifndef __RULES__
#define __RULES__

#include "Cell.h"
#include "Chunk.h"

namespace Conway
{
	class Rules
	{
	public:
		static std::array<Cell, 8> GetCellNeigbors(const Chunk16* chunk, const Vector2Int pos);
		
		static int PopulationCount(std::array<Cell, 8> cells);

		static Cell Evolve(const Cell cell, std::array<Cell, 8> neighbors);

		static void EvolveChunk(Chunk16*& gen0, Chunk16*& gen1);

		static void Display(const Chunk16* chunk);
	};
}

#endif // __RULES__
