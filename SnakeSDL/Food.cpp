#include "Food.h"
#include "Coordinate.h"
#include "Snake.h"
#include <random>
#include <thread>
#include <chrono>
#include "Board.h"

Food::Food(SDL_Renderer* renderer, Board& board) : board(board)
{
    makeNew();

    texture.loadFromFile(renderer, "../Resources/images/apple.png");

    textureSpriteClips[0] = { 0, 0, 10, 10 };
    textureSpriteClips[1] = { 10, 0, 10, 10 };
    textureSpriteClips[2] = { 20, 0, 10, 10 };
    textureSpriteClips[3] = { 30, 0, 10, 10 };
}

bool Food::isValidCoord(int x, int y)
{
    for (const auto& coord : board.getSnake().getBody()) {

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
    texture.free();
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

void Food::render(SDL_Renderer* renderer, int screenWidth, int screenHeight, int currentClip)
{
    texture.render(renderer, (screenWidth - board.getWidth() * 10) / 2 + location.getX() * 10,
        (screenHeight - board.getHeight() * 10) / 2 + location.getY() * 10, &textureSpriteClips[currentClip]);
}