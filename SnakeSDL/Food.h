#pragma once
#include "Coordinate.h"
#include "Snake.h"

class Food
{
private:
	// Square the food is located in
	Coordinate location;
	// Board info
	Board& board;

	bool isValidCoord(int x, int y);

public:
	//
	Food(Board& board);

	~Food();

	void free();

	int getX() const;

	int getY() const;

	void makeNew();
};

