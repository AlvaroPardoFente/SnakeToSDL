#pragma once
#include "Snake.h"
#include "Food.h"
#include "LTexture.h"
#include <SDL.h>
#include <vector>

class Board
{
private:
	// One snake
	Snake* snake;

	// One instance of food
	Food* food;

	// Board texture sprite
	LTexture groundTexture;
	LTexture wallTexture;
	
	// Board dimensions
	int boardWidth;
	int boardHeight;
	std::vector<std::vector<int>> boardLayout;
	SDL_Rect groundSpriteClips[4];
	SDL_Rect wallSpriteClips[2];

public:
	// Board initialization with snake and food
	Board(SDL_Renderer* renderer, int width, int height);

	~Board();

	void free();

	int getWidth() const;

	int getHeight() const;

	Food& getFood();

	Snake& getSnake();

	void render(SDL_Renderer* renderer, int screenWidth, int screenHeight);
};

