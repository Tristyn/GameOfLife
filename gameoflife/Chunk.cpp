#include "Chunk.h"
#include "Cell.h"
#include "Rules.h"
#include "Vector2.h"

namespace Conway
{
	template<size_t _SizeX, size_t _SizeY>
	Chunk<_SizeX, _SizeY>::Chunk()
	{
		mCells = new std::array<Cell, kCapacity>();
	}

	template<size_t _SizeX, size_t _SizeY>
	Chunk<_SizeX, _SizeY>::Chunk(std::array<Cell, kCapacity>* cells)
		: mCells(nullptr)
	{
		if (cells)
		{
			mCells = new std::array<Cell, kCapacity>(*cells);
		}
	}

	// Chunk will be implementing rule of 5, a C++11 way to avoid copies. Using the move constructor,
	// the chunk will copy it's internal std::array pointer to the new object, leaving the moved
	// object in a 'moved' state. The manager can avoid allocations by tracking which chunks are unpopulated,
	// and when a chunk needs population we will reuse the array of an unpopulated chunk if possible. 
	template<size_t _SizeX, size_t _SizeY>
	Chunk<_SizeX, _SizeY>::Chunk(const Chunk& other) // Copy constructor
		: Chunk(other.mCells)
	{

	}

	// Notice I'm using mCells(std::exchange(other.mCells, nullptr)) instead of 
	// std::swap(mCells, other.mCells), I can't trust that mCells has already been
	// zero initialized because someone could call my constructor on junk memory.
	// Avoiding reading junk is the real deal, memory corruption is serious.
	template<size_t _SizeX, size_t _SizeY>
	Chunk<_SizeX, _SizeY>::Chunk(Chunk&& other) noexcept // Move constructor
		: mCells(std::exchange(other.mCells, nullptr)) 
	{

	}

	template<size_t _SizeX, size_t _SizeY>
	Chunk<_SizeX, _SizeY>& Chunk<_SizeX, _SizeY>::operator=(const Chunk& other) // Copy Assignment
	{
		// This is a bit of insanity in one line
		// - rvalue Chunk(other) is constructed as a copy of other
		// - move assignment operator is called, all fields of this and Chunk(other) swap
		// - this is returned, which now contains members passed in by other
		// - Chunk(other).~Chunk() is called, deleting everything that used to be this (because this is getting overwritten)

		// You coud alternatively do
		// std::swap(mCells, other.mCells);
		// return *this;
		return *this = Chunk(other);
	}

	template<size_t _SizeX, size_t _SizeY>
	Chunk<_SizeX, _SizeY>& Chunk<_SizeX, _SizeY>::operator=(Chunk&& other) noexcept // Move Assignment
	{
		std::swap(mCells, other.mCells);
		return *this;
	}


	template<size_t _SizeX, size_t _SizeY>
	Chunk<_SizeX, _SizeY>::~Chunk() // Destructor
	{
		delete mCells;
	}

	template<size_t _SizeX, size_t _SizeY>
	size_t Chunk<_SizeX, _SizeY>::GetIndex(const Vector2Int pos) const
	{
		if (pos.GetX() < 0 || pos.GetX() >= _SizeX)
		{
			throw new std::out_of_range("x out of range");
		}
		if (pos.GetY() < 0 || pos.GetY() >= _SizeY)
		{
			throw new std::out_of_range("y out of range");
		}
		return pos.GetX() + (pos.GetY() * _SizeX);
	}

	template<size_t _SizeX, size_t _SizeY>
	Cell Chunk<_SizeX, _SizeY>::GetCell(const Vector2Int pos) const
	{
		if (pos.GetX() < 0 || pos.GetX() >= _SizeX)
		{
			return Cell::dead;
		}
		if (pos.GetY() < 0 || pos.GetY() >= _SizeY)
		{
			return Cell::dead;
		}
		size_t index = GetIndex(pos);
		return (*mCells)[index];
	}

	template<size_t _SizeX, size_t _SizeY>
	void Chunk<_SizeX, _SizeY>::SetCell(const Vector2Int pos, const Cell cell)
	{
		size_t index = GetIndex(pos);
		(*mCells)[index] = cell;
	}

	template<size_t _SizeX, size_t _SizeY>
	std::array<Conway::Cell, 8> Chunk<_SizeX, _SizeY>::GetCellNeigbors(const Vector2Int pos)
	{
		// Moore neighborhood
		std::array<Conway::Cell, 8> array = {};
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

	template<size_t _SizeX, size_t _SizeY>
	void Chunk<_SizeX, _SizeY>::Iterate(Chunk*& gen0, Chunk*& gen1)
	{
		for (int x = 0; x < _SizeX; x++)
		{
			for (int y = 0; y < _SizeY; y++)
			{
				Vector2Int pos = Vector2Int(x, y);
				const Cell cell = gen0->GetCell(pos);
				std::array<Cell, 8> neighbors = gen0->GetCellNeigbors(pos);
				gen1->SetCell(pos, Rules::Iteration(cell, neighbors));
			}
		}
		std::swap(gen0, gen1);
	}

	template<size_t _SizeX, size_t _SizeY>
	void Chunk<_SizeX, _SizeY>::Display(const Chunk* chunk)
	{
		for (int x = 0; x < _SizeX; x++)
		{
			for (int y = 0; y < _SizeY; y++)
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

	// To be able to use these templated functions every concrete
	// class must be defined. This is an issue for modularity,
	// single responsibility and seperation of concerns.
	// The only way to avoid this is define templated functions
	// in Chunk.h, or include a *.tpp implementation file at the
	// end of Chunk.h.

	// Explicit template instantiation
	template class Chunk<16, 16>;
}
