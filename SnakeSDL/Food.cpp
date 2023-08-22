#include "Food.h"
#include "Coordinate.h"
#include "Snake.h"
#include <random>
#include <thread>
#include <chrono>

Food::Food(Board& board) : board(board)
{
    makeNew();
}

bool Food::isValidCoord(int x, int y)
{
    for (const Coordinate& coord : board.getSnake().getBody()) {

        if (coord.getX() == x && coord.getY() == y) {
            return false;
        }
    }

    return true;
}

Food::~Food()
{

    free();
}

void Food::free()
{
}

int Food::getX() const
{
	return location.getX();
}

int Food::getY() const
{
	return location.getY();
}

void Food::makeNew()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribX(0, board.getWidth());
    std::uniform_int_distribution<int> distribY(0, board.getHeight());
    bool isCoordTaken = false;
    int randomX;
    int randomY;

    do {
        randomX = distribX(gen);
        randomY = distribY(gen);

    } while (!isValidCoord(randomX, randomY));

    location = Coordinate(randomX, randomY, board.getWidth(), board.getHeight());
}
