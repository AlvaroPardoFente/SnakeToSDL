#include "Board.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <random>


Board::Board(SDL_Renderer* renderer, int width, int height) : boardWidth(width),
	boardHeight(height)
{
	groundTexture.loadFromFile(renderer, "../Resources/Images/ground.png");
	wallTexture.loadFromFile(renderer, "../Resources/Images/wall.png");

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribSprite(0, 4);

	for (int row = 0; row < width + 2; ++row) {
		std::vector<int> rowVector; // Create a row vector for each row

		for (int col = 0; col < height + 2; ++col) {
			int value = distribSprite(gen);
			rowVector.push_back(value); // Add element to the row vector
		}

		boardLayout.push_back(rowVector); // Add the row vector to the 2D vector
	}

	groundSpriteClips[0] = { 0, 0, 10, 10 };
	groundSpriteClips[1] = { 10, 0, 10, 10 };
	groundSpriteClips[2] = { 20, 0, 10 ,10 };
	groundSpriteClips[3] = { 30, 0, 10, 10 };

	wallSpriteClips[0] = { 0, 0, 10, 10 };
	wallSpriteClips[1] = { 10, 0, 10, 10 };

	snake = new Snake(renderer, boardWidth / 2, boardHeight / 2, 3, *this);
	food = new Food(renderer, *this);
}

Board::~Board()
{

	free();
}

void Board::free()
{
	delete snake;
	delete food;
	snake = NULL;
	food = NULL;
	boardWidth = 0;
	boardHeight = 0;

	groundTexture.free();
	wallTexture.free();
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
	return *food;
}

Snake& Board::getSnake()
{
	return *snake;
}

void Board::render(SDL_Renderer* renderer, int screenWidth, int screenHeight)
{
	int scaledBoardWidth = boardWidth * 10;
	int scaledBoardHeight = boardHeight * 10;

	//Ground rendering based on random seed
	for (int i = 0; i < boardLayout.size(); i++)
	{
		for (int j = 0; j < boardLayout[i].size(); j++)
		{
			groundTexture.render(renderer, (screenWidth - scaledBoardWidth) / 2 - 10 + (i * 10), (screenHeight - scaledBoardHeight) / 2 - 10 + (j * 10), &groundSpriteClips[boardLayout[i][j]]);
		}
	}

	//Corner rendering
	wallTexture.render(renderer, (screenWidth - scaledBoardWidth) / 2 - 10, (screenHeight - scaledBoardHeight) / 2 - 10, &wallSpriteClips[1]);
	wallTexture.render(renderer, (screenWidth - scaledBoardWidth) / 2 + scaledBoardWidth, (screenHeight - scaledBoardHeight) / 2 - 10, &wallSpriteClips[1]);
	wallTexture.render(renderer, (screenWidth - scaledBoardWidth) / 2 - 10, (screenHeight - scaledBoardHeight) / 2 + scaledBoardHeight, &wallSpriteClips[1]);
	wallTexture.render(renderer, (screenWidth - scaledBoardWidth) / 2 + scaledBoardWidth, (screenHeight - scaledBoardHeight) / 2 + scaledBoardHeight, &wallSpriteClips[1]);

	//Wall rendering with rotation
	for (int i = 0; i < boardWidth; i++)
	{
		wallTexture.render(renderer, (screenWidth - scaledBoardWidth) / 2 + (i * 10), (screenHeight - scaledBoardHeight) / 2 - 10, &wallSpriteClips[0]);
		wallTexture.render(renderer, (screenWidth - scaledBoardWidth) / 2 + (i * 10), (screenHeight - scaledBoardHeight) / 2 + scaledBoardHeight, &wallSpriteClips[0], 180);
	}
	for (int i = 0; i < boardHeight; i++)
	{
		wallTexture.render(renderer, (screenWidth - scaledBoardWidth) / 2 - 10, (screenHeight - scaledBoardHeight) / 2 + (i * 10), &wallSpriteClips[0], 270);
		wallTexture.render(renderer, (screenWidth - scaledBoardWidth) / 2 + scaledBoardWidth, (screenHeight - scaledBoardHeight) / 2 + (i * 10), &wallSpriteClips[0], 90);
	}
}