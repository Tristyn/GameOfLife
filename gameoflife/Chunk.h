#ifndef __CHUNK__
#define __CHUNK__
#include <iostream>
#include <array>
#include <stdexcept>
#include "Cell.h"
#include "Vector2.h"
namespace Conway
{
	template<size_t _SizeX, size_t _SizeY>
	class Chunk
	{
		// Define the constant of the underlying array
		// We'll be using this in a couple of places.
		static const size_t kCapacity = _SizeX * _SizeY;

	private:
		std::array<Cell, kCapacity>* mCells;
	public:
		Chunk();
		Chunk(std::array<Cell, kCapacity>* cells);

		// Rule of 5
		Chunk(const Chunk& other); // Copy constructor
		Chunk(Chunk&& other) noexcept; // Move constructor
		Chunk& operator=(const Chunk& other); // Copy Assignment
		Chunk& operator=(Chunk&& other) noexcept; // Move Assignment
		~Chunk(); // Destructor

		size_t GetIndex(const Vector2Int pos) const;
		Cell GetCell(const Vector2Int pos) const;
		void SetCell(const Vector2Int pos, const Cell cell);
		std::array<Conway::Cell, 8> GetCellNeigbors(const Vector2Int pos);

		static void Iterate(Chunk*& gen0, Chunk*& gen1);
		static void Display(const Chunk* chunk);
	};

	// Define common types we'll use
	typedef Chunk<16, 16> Chunk16;
}
#endif // __CHUNK__