#ifndef  __RULES__
#define __RULES__

#include "Cell.h"

namespace Conway
{
	class Rules
	{
	public:
		template<size_t _Size>
		static int PopulationCount(std::array<Cell, _Size>  cells);
		static Cell Iteration(const Cell cell, std::array<Cell, 8> neighbors);
	};
}

#endif // __RULES__
