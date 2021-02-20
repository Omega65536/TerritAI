#pragma once

#include "moveList.h"
#include "board.h"

namespace MoveGenerator {
	void precomputeBitboards();
	MoveList generateMoves(const Board& board);
	int countMoves(const Board& board);
}