#pragma once
#include "Coordinate.h"
#include "Snake.h"
#include "LTexture.h"
#include <SDL.h>

class Board;

class Food
{
private:
	// Square the food is located in
	Coordinate location;
	
	// Board info
	Board& board;
	
	// Apple texture
	LTexture texture;

	SDL_Rect textureSpriteClips[4];

	bool isValidCoord(int x, int y);

public:
	//
	Food(SDL_Renderer* renderer, Board& board);

	~Food();

	void free();

	int getX() const;

	int getY() const;

	void makeNew();

	void render(SDL_Renderer* renderer, int screenWidth, int screenHeight, int currentClip);
};

