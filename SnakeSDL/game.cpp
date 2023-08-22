#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "Board.h"
#include "DirEnum.h"
#include "SnakeFlags.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int BOARD_WIDTH = 20;
const int BOARD_HEIGHT = 20;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene texturegPromptTexture
LTexture ;

//The music that will be played
Mix_Music* gMusic = NULL;

//The sound effects that will be used
Mix_Chunk* gScratch = NULL;

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load prompt texture
	if (!gPromptTexture.loadFromFile(gRenderer, "../../tutorials/21_sound_effects_and_music/prompt.png"))
	{
		printf("Failed to load prompt texture!\n");
		success = false;
	}

	//Load music
	gMusic = Mix_LoadMUS("../../tutorials/21_sound_effects_and_music/beat.wav");
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//Load sound effects
	gScratch = Mix_LoadWAV("../../tutorials/21_sound_effects_and_music/scratch.wav");
	if (gScratch == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gPromptTexture.free();

	//Free the sound effects
	Mix_FreeChunk(gScratch);
	gScratch = NULL;

	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			Board board = Board(BOARD_WIDTH, BOARD_HEIGHT);

			Dir currentDir = Dir::up;

			uint8_t moveResult = MOVE;

			bool processedInput = false;

			//While application is running
			while (!quit)
			{
				processedInput = false;
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					//Handle key press
					else if (e.type == SDL_KEYDOWN && !processedInput)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_UP:
							currentDir = Dir::up;
							processedInput = true;
							break;
						case SDLK_DOWN:
							currentDir = Dir::down;
							processedInput = true;
							break;
						case SDLK_LEFT:
							currentDir = Dir::left;
							processedInput = true;
							break;
						case SDLK_RIGHT:
							currentDir = Dir::right;
							processedInput = true;
							break;

						}
					}
				}

				//Game logic
				moveResult = board.getSnake().move(currentDir);
				if (moveResult & GAME_OVER) quit = true;
				if (moveResult & FOOD_EATEN)
				{
					//TODO: Incrementar velocidad
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render prompt
				gPromptTexture.render(gRenderer, 0, 0);

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}