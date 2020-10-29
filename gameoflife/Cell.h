#include <cstdint>
#pragma once

namespace Conway
{
	enum class cell_state : uint8_t
	{
		kDead = 0,
		kAlive = 1
	};

	class Cell
	{
	public:
		static const Cell alive;
		static const Cell dead;

		Cell();
		constexpr Cell(Conway::cell_state aCellState) : m_value(aCellState) { }
		constexpr operator const Conway::cell_state() const { return m_value; };
		explicit operator bool() = delete;

		static const Cell Iteration(const Cell* cell, const std::array<const Cell*, 8> neighbors);

		template<size_t _Size>
		static int PopulationCount(const std::array<const Cell*, _Size>  cells)
		{
			int count = 0;
			for (const Cell* const cell : cells)
			{
				switch (*cell)
				{
				case Conway::cell_state::kAlive:
					count++;
					break;
				}
			}
			return count;
		}

	private:
		Conway::cell_state m_value;
	};
}