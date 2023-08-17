#pragma once

#include "AnimatedTexture.h"
#include "Input.h"
#include"Sprite.h"
#include "AudioManager.h"
#include "SceneManager.h"
#include "Timer.h"
#include "PhysicsManager.h"

class GameManager
{
private:
	static GameManager* instance;

	const int FRAME_RATE = 144;
	const int PHYSICS_FRAME_RATE = 60;

	bool mQuit;
	Graphics* mGraphics;
	AssetManager* mAssetMgr;
	AudioManager* mAudioMgr;
	PhysicsManager* mPhysMgr;
	SceneManager* mSceneMgr;

	SDL_Rect camRect;

	Timer* mTimer;

	SDL_Event mEvent;

	AnimatedTexture* mTex;

	Sprite* sprite;

	InputManager* mInputMgr;

	Texture* text;

public:
	static GameManager* Instance();
	static void Release();
	bool isDebug;

	void Run();

	SceneManager* GetSceneManager() { return mSceneMgr; }

private:
	GameManager();
	~GameManager();
};