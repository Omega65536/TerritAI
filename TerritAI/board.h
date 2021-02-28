#pragma once

#include <stdint.h>
#include <iostream>
#include "square.h"

#define ZERO_BB 0ULL
#define ONE_BB 1ULL

typedef uint64_t Bitboard;

struct Board {
	Bitboard white;
	Bitboard black;
	bool whiteToMove;
	int d_boards;
	int d_score;

	Square moves[64];
	int numMoves;

	Board();

	void move(const Square move);
	void undoMove();

	int getStatus();
	std::string toString();
};