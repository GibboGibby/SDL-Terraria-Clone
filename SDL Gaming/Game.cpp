#include "Game.h"
#include "TestObject.h"
#include <iostream>
#include "Input.h"




Game::Game() {}

bool Game::Init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "SDL init success\n";
		gameWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (gameWindow != 0)
		{
			std::cout << "Window creating success\n";
			gameRenderer = SDL_CreateRenderer(gameWindow, -1, 0);
			if (gameRenderer != 0)
			{
				std::cout << "Renderer creation success\n";
				SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 255);
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;

	gameRunning = true;

	gameObjects.push_back(new TestObject());
	//gameObjects.push_back(new TestObject());
	//gameObjects.push_back(new TestObject());
	//gameObjects.push_back(new TestObject());
	//gameObjects.push_back(new TestObject());

	lastFrameTime = std::chrono::high_resolution_clock::now();
	curTime = lastFrameTime;

	return true;
}

void Game::Render()
{
	SDL_SetRenderDrawColor(gameRenderer, 0, 0, 0, 255);
	SDL_RenderClear(gameRenderer);

	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Render();
	}

	

	SDL_RenderPresent(gameRenderer);
}

void Game::Update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->Update();
	}
}

void Game::HandleEvents()
{
	SDL_Event event;
	while ((SDL_PollEvent(&event)) != 0)
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;
		default:
			break;
		}
	}
}

void Game::Clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(gameWindow);
	SDL_DestroyRenderer(gameRenderer);
	SDL_Quit();
}