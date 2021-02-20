#pragma once

#include "square.h"

struct MoveList {
	Square moves[64];
	int numMoves;

	MoveList();
	inline void clear();
	inline void addMove(const Square move) {
		moves[numMoves] = move;
		numMoves++;
	}
};