#include <iostream>
#include "Cell.h"
#include "Chunk.h"
#include "Vector2.h"

struct IUnknown; // Workaround for "combaseapi.h(229): error C2187: syntax error: 'identifier' was unexpected here"
#include "windows.h"
int main()
{
	Conway::Chunk16* gen0 = new Conway::Chunk16();
	Conway::Chunk16* gen1 = new Conway::Chunk16();

	// Block
	gen0->SetCell(Conway::Vector2Int(10, 5), Conway::Cell::alive);
	gen0->SetCell(Conway::Vector2Int(10, 6), Conway::Cell::alive);
	gen0->SetCell(Conway::Vector2Int(11, 5), Conway::Cell::alive);
	gen0->SetCell(Conway::Vector2Int(11, 6), Conway::Cell::alive);

	// Blinker
	gen0->SetCell(Conway::Vector2Int(2, 2), Conway::Cell::alive);
	gen0->SetCell(Conway::Vector2Int(2, 3), Conway::Cell::alive);
	gen0->SetCell(Conway::Vector2Int(2, 4), Conway::Cell::alive);

	// Glider
	gen0->SetCell(Conway::Vector2Int(6, 6), Conway::Cell::alive);
	gen0->SetCell(Conway::Vector2Int(7, 7), Conway::Cell::alive);
	gen0->SetCell(Conway::Vector2Int(5, 8), Conway::Cell::alive);
	gen0->SetCell(Conway::Vector2Int(6, 8), Conway::Cell::alive);
	gen0->SetCell(Conway::Vector2Int(7, 8), Conway::Cell::alive);

	while (true)
	{
		system("CLS");
		Conway::Chunk16::Display(gen0);
		Sleep(350);
		Conway::Chunk16::Iterate(gen0, gen1);
	}
}
