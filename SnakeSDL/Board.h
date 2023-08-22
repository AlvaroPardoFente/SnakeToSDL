#pragma once
#include "Snake.h"
#include "Food.h"

class Board
{
private:
	// One snake
	Snake snake;

	// One instance of food
	Food food;
	
	// Board dimensions
	int boardWidth;
	int boardHeight;

public:
	// Board initialization with snake and food
	Board(int width, int height);

	~Board();

	void free();

	int getWidth() const;

	int getHeight() const;

	Food& getFood();

	Snake& getSnake();
};

