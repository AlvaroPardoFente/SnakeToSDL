#pragma once
#include "SnakeCoordinate.h"
#include <list>
#include "DirEnum.h"
#include "LTexture.h"
#include <SDL.h>

class Board;

class Snake
{
private:
	//Snake body as a set of coordinates
	std::list<SnakeCoordinate> body;
	Board& board;


	LTexture texture;
	SDL_Rect textureSpriteClips[4];

	bool isEating(const Coordinate newCoord);

public:

	Snake(SDL_Renderer* renderer, int x, int y, int startingSize, Board& board);

	~Snake();

	void free();

	uint8_t move(Dir dir);

	std::list<SnakeCoordinate> getBody();

	void render(SDL_Renderer* render, int screenWidth, int screenHeight);
};

