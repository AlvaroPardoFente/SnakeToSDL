#include "Board.h"

Board::Board(int width, int height) : boardWidth(width),
	boardHeight(height), 
	snake(width / 2, height / 2, 3, *this),
	food(*this)
{
}

Board::~Board()
{

	free();
}

void Board::free()
{
	delete(&snake);
	delete(&food);
	boardWidth = 0;
	boardHeight = 0;
}

int Board::getWidth() const
{
	return boardWidth;
}

int Board::getHeight() const
{
	return boardHeight;
}

Food& Board::getFood()
{
	return food;
}

Snake& Board::getSnake()
{
	return snake;
}
