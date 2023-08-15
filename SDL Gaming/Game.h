#ifndef __Game__
#define __Game__
#include "SDL.h"
#include <vector>
#include "GameObject.h"
#include <chrono>

#define FPSMAX 60
class Game
{
private:
	std::vector<GameObject*> gameObjects;
public:
	
	Game();
	~Game();
	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void Render();
	void Update();
	void HandleEvents();
	void Clean();
	bool Running() { return gameRunning; }
private:
	SDL_Window* gameWindow;
	SDL_Renderer* gameRenderer;
	bool gameRunning;
	double secondsBetweenFrames = (1 / FPSMAX) * 1000;
	std::chrono::steady_clock::time_point lastFrameTime, curTime;
};
#endif