#include <chrono>
#include <algorithm>
#include <random>
#include "engine.h"
#include "board.h"
#include "moveGenerator.h"
#include "moveList.h"
#include "square.h"

Square Engine::getMove(int maxTime, Board& board) {
	board.d_boards = 0;
	Square bestMove = C8;
	int d = 2;

	auto start = std::chrono::system_clock::now();
	while (true) {
		bestMove = findBestMove(d, board);
		d += 2;

		auto now = std::chrono::system_clock::now();
		int time = std::chrono::duration_cast<std::chrono::microseconds>(now - start).count();
		if (time >= maxTime) {
			break;
		}
	}

	std::cout << "Move: " << squareToString(bestMove) << "    Score: " << board.d_score << "\n";
	std::cout << "Depth: " << d << "    Nodes: " << board.d_boards << "    Time: " << time << "\n";
	return bestMove;
}

Square Engine::findBestMove(int depth, Board& board) {
	Square bestmove = C8;
	int bestscore = -9999;
	int alpha = -10'000;
	int beta = 10'000;

	MoveList moveList = MoveGenerator::generateMoves(board);
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	shuffle(&moveList.moves[0], &moveList.moves[moveList.numMoves], std::default_random_engine(seed));
	for (int i = 0; i < moveList.numMoves; i++) {
		board.move(moveList.moves[i]);
		int score = search(-beta, -alpha, depth - 1, board);
		board.undoMove();

		std::cout << "M: " << squareToString(moveList.moves[i]) << "    S: " << score << "\n";
		if (score > bestscore) {
			bestscore = score;
			board.d_score = score;
			bestmove = moveList.moves[i];
		}
		if (score > alpha) {
			alpha = score;
		}
	}
	return bestmove;
}

int Engine::search(int alpha, int beta, int depth, Board& board) {
	int bestscore = -999;
	if (depth == 0) {
		return -evaluate(board);
	}
	MoveList moveList = MoveGenerator::generateMoves(board);
	for (int i = 0; i < moveList.numMoves; i++) {
		board.move(moveList.moves[i]);
		int score = -search(-beta, -alpha, depth - 1, board);
		board.undoMove();
		if (score >= beta) {
			return score;
		}
		if (score > bestscore) {
			bestscore = score;
		}
		if (score > alpha) {
			alpha = score;
		}
	}
	return bestscore;
}

int Engine::evaluate(Board& board) {
	board.d_boards++;

	int score = 0;
	bool orgColor = board.whiteToMove;

	board.whiteToMove = true;
	score += MoveGenerator::countMoves(board);

	board.whiteToMove = false;
	score -= MoveGenerator::countMoves(board);

	board.whiteToMove = orgColor;
	return board.whiteToMove ? score : - score;
}

Square Engine::getMoveMC(int games, Board& board) {
	int bestscore = -games;
	Square bestmove = C8;

	MoveList moveList = MoveGenerator::generateMoves(board);
	for (int i = 0; i < moveList.numMoves; i++) {
		board.move(moveList.moves[i]);
		int score = board.whiteToMove ? -monteCarlo(games, board) : monteCarlo(games, board);
		board.undoMove();

		std::cout << squareToString(moveList.moves[i]) << ": " << score << "\n";

		if (score > bestscore) {
			bestscore = score;
			board.d_score = score;
			bestmove = moveList.moves[i];
		}
	}

	return bestmove;
}

int Engine::monteCarlo(int games, Board& board) {
	int score = 0;

	for (int i = 0; i < games; i++) {
		int depth = 0;
		MoveList moveList = MoveGenerator::generateMoves(board);

		while (moveList.numMoves != 0) {
			int i = rand() % moveList.numMoves;
			Square move = moveList.moves[i];
			depth++;
			board.move(move);
			moveList = MoveGenerator::generateMoves(board);
		}

		score += board.whiteToMove ? -1 : 1;
		for (int i = 0; i < depth; i++) {
			board.undoMove();
		}
	}
	
	return score;
}