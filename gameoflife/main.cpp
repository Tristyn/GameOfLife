#include <iostream>
#include "Rules.h"
#include "Cell.h"
#include "Chunk.h"
#include "Vector2.h"

struct IUnknown; // Workaround for "combaseapi.h(229): error C2187: syntax error: 'identifier' was unexpected here"
#include "windows.h"

int main()
{
	// Create 2 buffers that will swap each generation
	// This avoids an O(n) memcpy when gen1 is computed and copied to gen0
	Conway::Chunk16* gen0 = new Conway::Chunk16();
	Conway::Chunk16* gen1 = new Conway::Chunk16();

	// In lieu of an editor, create some life forms
	// Block
	gen0->SetCell(Conway::Vector2Int(10, 5), Conway::Cell::kAlive);
	gen0->SetCell(Conway::Vector2Int(10, 6), Conway::Cell::kAlive);
	gen0->SetCell(Conway::Vector2Int(11, 5), Conway::Cell::kAlive);
	gen0->SetCell(Conway::Vector2Int(11, 6), Conway::Cell::kAlive);

	// Blinker
	gen0->SetCell(Conway::Vector2Int(2, 2), Conway::Cell::kAlive);
	gen0->SetCell(Conway::Vector2Int(2, 3), Conway::Cell::kAlive);
	gen0->SetCell(Conway::Vector2Int(2, 4), Conway::Cell::kAlive);

	// Glider
	gen0->SetCell(Conway::Vector2Int(6, 6), Conway::Cell::kAlive);
	gen0->SetCell(Conway::Vector2Int(7, 7), Conway::Cell::kAlive);
	gen0->SetCell(Conway::Vector2Int(5, 8), Conway::Cell::kAlive);
	gen0->SetCell(Conway::Vector2Int(6, 8), Conway::Cell::kAlive);
	gen0->SetCell(Conway::Vector2Int(7, 8), Conway::Cell::kAlive);

	while (true)
	{
		// Update
		Sleep(350);
		Conway::Rules::EvolveChunk(gen0, gen1);

		// Draw
		system("CLS"); // Clear terminal
		Conway::Rules::Display(gen0);

	}
}
