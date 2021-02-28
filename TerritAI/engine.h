#pragma once

#include "board.h"
#include "square.h"

namespace Engine {
	Square getMove(int nodes, Board& board);
	Square findBestMove(int depth, Board& board);
	int search(int alpha, int beta, int depth, Board& board);
	int evaluate(Board& board);

	Square getMoveMC(int games, Board& board);
	int monteCarlo(int games, Board& board);
}