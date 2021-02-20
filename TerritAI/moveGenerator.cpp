#include <string>
#include "moveGenerator.h"
#include "moveList.h"

Bitboard ADJ_ALL_BB[64];
Bitboard ADJ_EDGES_BB[64];
Bitboard ADJ_CORNERS_BB[64];

void MoveGenerator::precomputeBitboards() {
	for (Square s = 0; s < 64; s++) {
		if (canGoNorthWest(s)) {
			ADJ_ALL_BB[s] |= ONE_BB << (s + NORTHWEST);
			ADJ_CORNERS_BB[s] |= ONE_BB << (s + NORTHWEST);
		}
		if (canGoNorth(s)) {
			ADJ_ALL_BB[s] |= ONE_BB << (s + NORTH);
			ADJ_EDGES_BB[s] |= ONE_BB << (s + NORTH);
		}
		if (canGoNorthEast(s)) {
			ADJ_ALL_BB[s] |= ONE_BB << (s + NORTHEAST);
			ADJ_CORNERS_BB[s] |= ONE_BB << (s + NORTHEAST);
		}
		if (canGoEast(s)) {
			ADJ_ALL_BB[s] |= ONE_BB << (s + EAST);
			ADJ_EDGES_BB[s] |= ONE_BB << (s + EAST);
		}
		if (canGoSouthEast(s)) {
			ADJ_ALL_BB[s] |= ONE_BB << (s + SOUTHEAST);
			ADJ_CORNERS_BB[s] |= ONE_BB << (s + SOUTHEAST);
		}
		if (canGoSouth(s)) {
			ADJ_ALL_BB[s] |= ONE_BB << (s + SOUTH);
			ADJ_EDGES_BB[s] |= ONE_BB << (s + SOUTH);
		}
		if (canGoSouthWest(s)) {
			ADJ_ALL_BB[s] |= ONE_BB << (s + SOUTHWEST);
			ADJ_CORNERS_BB[s] |= ONE_BB << (s + SOUTHWEST);
		}
		if (canGoWest(s)) {
			ADJ_ALL_BB[s] |= ONE_BB << (s + WEST);
			ADJ_EDGES_BB[s] |= ONE_BB << (s + WEST);
		}
	}
}

MoveList MoveGenerator::generateMoves(const Board& board) {
	const Bitboard& myBB = board.whiteToMove ? board.white : board.black;
	const Bitboard& enemyBB = board.whiteToMove ? board.black : board.white;

	MoveList moves;
	for (Square s = 0; s < 64; s++) {
		if ((myBB | enemyBB) & (ONE_BB << s)) {
			continue;
		}
		if ((enemyBB & ADJ_ALL_BB[s]) == 0) {
			moves.addMove(s);
			continue;
		}
		if (myBB & ADJ_EDGES_BB[s]) {
			moves.addMove(s);
			continue;
		}
		if ((enemyBB & ADJ_EDGES_BB[s]) == 0 && (myBB & ADJ_CORNERS_BB[s]) != 0) {
			moves.addMove(s);
			continue;
		}
	}
	return moves;
}

int MoveGenerator::countMoves(const Board& board) {
	const Bitboard& myBB = board.whiteToMove ? board.white : board.black;
	const Bitboard& enemyBB = board.whiteToMove ? board.black : board.white;

	int num = 0;
	for (Square s = 0; s < 64; s++) {
		if ((myBB | enemyBB) & (ONE_BB << s)) {
			continue;
		}
		if ((enemyBB & ADJ_ALL_BB[s]) == 0) {
			num++;
			continue;
		}
		if (myBB & ADJ_EDGES_BB[s]) {
			num++;
			continue;
		}
		if ((enemyBB & ADJ_EDGES_BB[s]) == 0 && (myBB & ADJ_CORNERS_BB[s]) != 0) {
			num++;
			continue;
		}
	}
	return num;
}