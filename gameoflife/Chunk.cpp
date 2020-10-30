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
	// object in a 'moved' state. You could imagine a manager implementing an infinite grid of chunks
	// that can avoid allocations by tracking which chunks are unpopulated,
	// and when a chunk needs population it will reuse the guts of an unpopulated chunk with move assignment. 
	template<size_t _SizeX, size_t _SizeY>
	Chunk<_SizeX, _SizeY>::Chunk(const Chunk& other) // Copy constructor
		: Chunk(other.mCells)
	{

	}

	// Notice I'm using mCells(std::exchange(other.mCells, nullptr)) instead of 
	// std::swap(mCells, other.mCells), I can't trust that mCells has already been
	// zero initialized because someone could call my constructor on junk memory,
	// then theres the potential for a random piece of memory at mCells to be freed later.
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

	/// <summary>
	/// Returns if the position is within the bounds of the chunk
	/// </summary>
	template<size_t _SizeX, size_t _SizeY>
	bool Chunk<_SizeX, _SizeY>::CellExists(const Vector2Int pos)
	{
		if (pos.GetX() < 0 || pos.GetX() >= _SizeX)
		{
			return false;
		}
		if (pos.GetY() < 0 || pos.GetY() >= _SizeY)
		{
			return false;
		}
		return true;
	}

	template<size_t _SizeX, size_t _SizeY>
	size_t Chunk<_SizeX, _SizeY>::GetIndex(const Vector2Int position)
	{
		if (!CellExists(position))
		{
			throw new std::out_of_range("position out of range");
		}
		return position.GetX() + (position.GetY() * _SizeX);
	}

	template<size_t _SizeX, size_t _SizeY>
	Cell Chunk<_SizeX, _SizeY>::GetCell(const Vector2Int pos) const
	{
		size_t index = GetIndex(pos);
		return (*mCells)[index];
	}

	template<size_t _SizeX, size_t _SizeY>
	void Chunk<_SizeX, _SizeY>::SetCell(const Vector2Int pos, const Cell cell)
	{
		size_t index = GetIndex(pos);
		(*mCells)[index] = cell;
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
