#include "Snake.h"
#include "Coordinate.h"
#include <list>
#include "DirEnum.h"
#include "Board.h"
#include "SnakeFlags.h"
#include "SnakeCoordinate.h"

int dirToAngle(Dir dir)
{
	int angle = 0;
	switch (dir)
	{
	case Dir::up:
		angle = 0;
		break;
	case Dir::right:
		angle = 90;
		break;
	case Dir::down:
		angle = 180;
		break;
	case Dir::left:
		angle = 270;
	}

	return angle;
}

SDL_RendererFlip turnToFlip(Turn turn)
{
	switch (turn)
	{
	case Turn::straight:
		return SDL_FLIP_NONE;
	case Turn::right:
		return SDL_FLIP_NONE;
	case Turn::left:
		return SDL_FLIP_HORIZONTAL;
	default:
		return SDL_FLIP_NONE;
	}
}

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

Snake::Snake(SDL_Renderer* renderer, int x, int y, int startingSize, Board& board) : board(board)
{
	if (startingSize < 1) startingSize = 1;
	else if (startingSize > board.getWidth()) startingSize = board.getWidth();
	body.clear();
	for (int i = 0; i < startingSize; i++)
	{
		body.push_back(SnakeCoordinate(x - i, y, board.getWidth(), board.getHeight(), Dir::right));
	}

	texture.loadFromFile(renderer, "../Resources/Images/snake.png");

	textureSpriteClips[0] = { 0, 0, 10, 10 };
	textureSpriteClips[1] = { 10, 0, 10, 10 };
	textureSpriteClips[2] = { 20, 0, 10, 10 };
	textureSpriteClips[3] = { 30, 0, 10, 10 };
}

Snake::~Snake()
{
	free();
}

void Snake::free()
{
	body.clear();
	texture.free();
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

	SnakeCoordinate newCoord = SnakeCoordinate(newX, newY, board.getWidth(), board.getHeight(), dir);

	if (!isEating(newCoord)) result += GAME_OVER;

	body.push_front(newCoord);
	if (newCoord.getX() == board.getFood().getX() && newCoord.getY() == board.getFood().getY())
	{
		board.getFood().makeNew();
		result += FOOD_EATEN;
	}
	else body.pop_back();

	Turn neckTurn = Turn::straight;
	SnakeCoordinate* neck = &*std::next(body.begin());
	switch (((static_cast<int>(newCoord.getOrientation())
		- static_cast<int>(neck->getOrientation())) + 4) % 4)
	{
	case 0:
		neckTurn = Turn::straight;
		break;
	case 1:
		neckTurn = Turn::right;
		break;
	case 3:
		neckTurn = Turn::left;
		break;
	}

	neck->setTurn(neckTurn);

	SnakeCoordinate* tail = &body.back();
	SnakeCoordinate oneBeforeTail = *std::prev(body.end(), 2);

	tail->setOrientation(oneBeforeTail.getOrientation());

	return result;
}

std::list<SnakeCoordinate> Snake::getBody()
{
	return body;
}

void Snake::render(SDL_Renderer* renderer, int screenWidth, int screenHeight)
{
	int headAngle = dirToAngle(body.front().getOrientation());
	
	texture.render(renderer, (screenWidth - board.getWidth() * 10) / 2 + body.front().getX() * 10,
		(screenHeight - board.getHeight() * 10) / 2 + body.front().getY() * 10, &textureSpriteClips[3], headAngle);

	for (auto it = std::next(body.begin()); it != std::prev(body.end()); ++it)
	{
		SDL_RendererFlip flip = turnToFlip(it->getTurn());
		int clip = 0;
		switch (it->getTurn())
		{
		case Turn::straight:
			clip = 0;
			break;
		case Turn::right:
			clip = 1;
			break;
		case Turn::left:
			clip = 1;
			break;
		}

		texture.render(renderer, (screenWidth - board.getWidth() * 10) / 2 + it->getX() * 10,
			(screenHeight - board.getHeight() * 10) / 2 + it->getY() * 10,
			&textureSpriteClips[clip], dirToAngle(it->getOrientation()), NULL, flip);
	}

	SnakeCoordinate tail = body.back();

	texture.render(renderer, (screenWidth - board.getWidth() * 10) / 2 + tail.getX() * 10,
		(screenHeight - board.getHeight() * 10) / 2 + tail.getY() * 10,
		&textureSpriteClips[2], dirToAngle(tail.getOrientation()));
}
