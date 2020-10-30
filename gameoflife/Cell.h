#ifndef __CELL__
#define __CELL__

#include <cstdint>

namespace Conway
{
	enum class CellState : uint8_t
	{
		kDead = 0,
		kAlive = 1
	};

	class Cell
	{
	private:
		Conway::CellState m_value;
	public:
		static const Cell kAlive;
		static const Cell kDead;

		Cell() = default;
		Cell(Conway::CellState aCellState);
		operator const Conway::CellState() const;
		explicit operator bool() = delete; // prevents if(cell)
	};
}
#endif // __CELL__