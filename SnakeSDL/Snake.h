#pragma once
#include "Coordinate.h"
#include <list>
#include "DirEnum.h"
#include "Board.h"

class Snake
{
private:
	//Snake body as a set of coordinates
	std::list<Coordinate> body;
	Board& board;

	bool isEating(const Coordinate newCoord);

public:

	Snake(int x, int y, int startingSize, Board& board);

	~Snake();

	void free();

	uint8_t move(Dir dir);

	std::list<Coordinate> getBody();
};

