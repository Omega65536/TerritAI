#pragma once

#include <stdint.h>
#include <iostream>
#include "square.h"
#include "board.h"

Board::Board() {
	white = ZERO_BB;
	black = ZERO_BB;
	whiteToMove = true;

	numMoves = 0;
}

void Board::move(const Square move) {
	Bitboard& myBitboard = whiteToMove ? white : black;
	whiteToMove = !whiteToMove;

	myBitboard |= ONE_BB << move;
	moves[numMoves] = move;
	numMoves++;
	//std::cout << "Move: " << SquareToString(move) << "\n";
	//std::cout << toString() << "\n";
}

void Board::undoMove() {
	whiteToMove = !whiteToMove;
	Bitboard& myBitboard = whiteToMove ? white : black;

	numMoves--;
	Square move = moves[numMoves];
	myBitboard &= ~(1ULL << move);
	//std::cout << "UnMove: " << SquareToString(moves[numMoves]) << "\n";
	//std::cout << toString() << "\n";
}

int getStatus() {
	return 0;
}

std::string Board::toString() {
	std::string o[8] = { "","","","","","","","" };
	for (Square x = 0; x < 8; x++) {
		for (Square y = 0; y < 8; y++) {
			if ((white >> (x * 8 + y)) & 1ULL)
				o[x] += "X";
			else if ((black >> (x * 8 + y)) & 1ULL)
				o[x] += "O";
			else
				o[x] += "-";

		}
	}

	return
		o[7] + "\n" +
		o[6] + "\n" +
		o[5] + "\n" +
		o[4] + "\n" +
		o[3] + "\n" +
		o[2] + "\n" +
		o[1] + "\n" +
		o[0] + "\n";
}