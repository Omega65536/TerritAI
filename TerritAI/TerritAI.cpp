#include <iostream>
#include <string>
#include <chrono>
#include "board.h"
#include "square.h"
#include "moveGenerator.h"
#include "engine.h"

int main() {

    Board board;
    MoveGenerator::precomputeBitboards();

    /*auto start = std::chrono::system_clock::now();
    Square move = Engine::findBestMove(9, board);
    auto stop = std::chrono::system_clock::now();
    int time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    std::cout << squareToString(move) << "\n";
    std::cout << time << "\n";*/

    auto start = std::chrono::system_clock::now();

   /* Square move;
    for (int i = 0; i < 32; i++) {
        move = Engine::findBestMove(4, board);
        board.move(move);

        std::cout << squareToString(move) << "\n";
        std::cout << board.toString() << "\n";

        move = Engine::findBestMove(8, board);
        board.move(move);

        std::cout << squareToString(move) << "\n";
        std::cout << board.toString() << "\n";
    }*/

    auto stop = std::chrono::system_clock::now();
    int time = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    //std::cout << time << std::endl;

    Square move;
    while (true) {
        std::string input;
        std::cin >> input;

        move = std::stoi(input);
        board.move(move);
        std::cout << squareToString(move) << "\n";
        std::cout << board.toString() << "\n";

        move = Engine::getMoveMC(100'000, board);
        board.move(move);
        std::cout << board.toString() << "\n";
    }
}