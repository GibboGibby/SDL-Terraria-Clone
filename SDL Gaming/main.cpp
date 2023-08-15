#include "Game.h"
#include "Input.h"
#include "GameManager.h"

#define FPS 144

Game* game = 0;

int main(int argc, char* argv[])
{

	GameManager* game = GameManager::Instance();
	const Uint32 fps = FPS;
	const Uint32 minframetime = 1000 / fps;

	//Uint32 frametime;
	InputManager* mInputMgr = InputManager::Instance();

	game->Run();

	GameManager::Release();
	game = NULL;
	return 0;
}