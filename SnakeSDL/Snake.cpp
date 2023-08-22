#include "Snake.h"
#include "Coordinate.h"
#include <list>
#include "DirEnum.h"
#include "Board.h"
#include "SnakeFlags.h"

bool Snake::isEating(const Coordinate newCoord)
{
	for (const Coordinate& pos : body)
	{
		if (pos.getX() == newCoord.getX() && pos.getY() == newCoord.getY())
		{
			return true;
		}
	}

	return false;
}

Snake::Snake(int x, int y, int startingSize, Board& board) : board(board)
{
	if (startingSize < 1) startingSize = 1;
	else if (startingSize > board.getWidth()) startingSize = board.getWidth();
	body.clear();
	for (int i = 0; i < startingSize; i++)
	{
		body.push_back(Coordinate(x - i, y, board.getWidth(), board.getHeight()));
	}
}

Snake::~Snake()
{
	free();
}

void Snake::free()
{
	body.clear();
}

uint8_t Snake::move(Dir dir)
{
	uint8_t result = MOVE;

	int newX, newY;

	newX = body.front().getX();
	newY = body.front().getY();

	switch (dir)
	{
	case Dir::up:
		newY--;
		break;
	case Dir::down:
		newY++;
		break;
	case Dir::left:
		newX--;
		break;
	case Dir::right:
		newX++;
		break;
	}

	Coordinate newCoord = Coordinate(newX, newY, board.getWidth(), board.getHeight());

	if (!isEating(newCoord)) result += GAME_OVER;

	body.push_front(newCoord);
	if (newCoord.getX() == board.getFood().getX() || newCoord.getY() == board.getFood().getY())
	{
		board.getFood().makeNew();
		result += FOOD_EATEN;
		// TODO: incrementar velocidad
	}
	else body.pop_back();

	return result;
}

std::list<Coordinate> Snake::getBody()
{
	return body;
}
