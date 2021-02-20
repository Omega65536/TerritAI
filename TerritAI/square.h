#pragma once

#include <stdint.h>
#include <iostream>

typedef uint8_t Square;

const Square NORTHWEST = 7;
const Square NORTH = 8;
const Square NORTHEAST = 9;
const Square EAST = 1;
const Square SOUTHEAST = -7;
const Square SOUTH = -8;
const Square SOUTHWEST = -9;
const Square WEST = -1;

enum squareNames {
	A1, B1, C1, D1, E1, F1, G1, H1,
	A2, B2, C2, D2, E2, F2, G2, H2,
	A3, B3, C3, D3, E3, F3, G3, H3,
	A4, B4, C4, D4, E4, F4, G4, H4,
	A5, B5, C5, D5, E5, F5, G5, H5,
	A6, B6, C6, D6, E6, F6, G6, H6,
	A7, B7, C7, D7, E7, F7, G7, H7,
	A8, B8, C8, D8, E8, F8, G8, H8
};

const std::string fileNames[8] = {
	"A", "B", "C", "D", "E", "F", "G", "H"
};

const std::string rankNames[8] = {
	"1", "2", "3", "4", "5", "6", "7", "8"
};

inline std::string squareToString(Square s) {
	return fileNames[s & 7] + rankNames[s >> 3];
}

inline bool canGoNorthWest(const Square s) {
	return ((s >> 3) != 7) && ((s & 7) != 0);
}

inline bool canGoNorth(const Square s) {
	return (s >> 3) != 7;
}

inline bool canGoNorthEast(const Square s) {
	return ((s >> 3) != 7) && ((s & 7) != 7);
}

inline bool canGoSouth(const Square s) {
	return (s >> 3) != 0;
}

inline bool canGoSouthEast(const Square s) {
	return ((s >> 3) != 0) && ((s & 7) != 7);
}

inline bool canGoEast(const Square s) {
	return (s & 7) != 7;
}

inline bool canGoSouthWest(const Square s) {
	return ((s >> 3) != 0) && ((s & 7) != 0);
}

inline bool canGoWest(const Square s) {
	return (s & 7) != 0;
}