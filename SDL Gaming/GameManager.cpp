#include "GameManager.h"
#include <iostream>

GameManager* GameManager::instance = NULL;


GameManager* GameManager::Instance()
{
	if (instance == NULL)
		instance = new GameManager();

	return instance;
}

void GameManager::Release()
{
	delete instance;
	instance = NULL;
}

GameManager::GameManager()
{
	mQuit = false;

	isDebug = true;

	mGraphics = Graphics::Instance();

	mAssetMgr = AssetManager::Instance();

	mInputMgr = InputManager::Instance();

	mAudioMgr = AudioManager::Instance();

	mSceneMgr = SceneManager::Instance();

	if (!Graphics::Initialized())
		mQuit = true;

	mTimer = Timer::Instance();

	

	//mTex = new AnimatedTexture("DuckSheet2.png", 1, 1, 13, 14, 4,0.5f,AnimatedTexture::HORIZONTAL);
	//mTex = new Texture("spritesheet.png");
	//mTex->Position(Vector2(Graphics::SCREEN_WIDTH * 0.3f, Graphics::SCREEN_HEIGHT * 0.3f));

	/*

	sprite = new Sprite("DuckSheet2.png", 1, 1, 13, 14);
	//sprite = new Sprite("DuckSheet2.png", 1, 1, 13, 14, 250, 0);


	sprite->Position(Vector2(Graphics::SCREEN_WIDTH * .5f, Graphics::SCREEN_HEIGHT * 0.5f));

	text = new Texture("Gaming!", "stocky.ttf", 72, {0, 0, 255});
	text->Position(Vector2(100, 200));

	*/

	

}

GameManager::~GameManager()
{
	AudioManager::Release();
	mAudioMgr = NULL;
	AssetManager::Release();
	mAssetMgr = NULL;

	Graphics::Release();
	mGraphics = NULL;

	Timer::Release();
	mTimer = NULL;

	InputManager::Release();
	mInputMgr = NULL;

	SceneManager::Release();
	mSceneMgr = NULL;

	delete mTex;
	mTex = NULL;

	delete text;
	text = NULL;

	delete sprite;
	sprite = NULL;
}

void GameManager::Run()
{
	while (!mQuit)
	{
		mTimer->Update();
		while (SDL_PollEvent(&mEvent) != 0)
		{
			switch (mEvent.type)
			{
			case SDL_QUIT:
				mQuit = true;
				break;
			default:
				break;
			}

			
		}
		if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE)
		{
			mGraphics->ClearBackBuffer();

			mInputMgr->Update();
			
#if _DEBUG
			if (mInputMgr->GetKeyDown(SDL_SCANCODE_1))
			{
				mSceneMgr->ChangeScene(SceneManager::SCENE_MAIN_MENU);
			}
			else if (mInputMgr->GetKeyDown(SDL_SCANCODE_2))
			{
				mSceneMgr->ChangeScene(SceneManager::SCENE_MAIN_GAME);
			}
#endif

			if (mInputMgr->GetKeyDown(SDL_SCANCODE_G))
			{
				for (int i = 0; i < 20; i++)
				{
					for (int j = 0; j < 11; j++)
					{
						GameObject* obj = mSceneMgr->GetScene()->AddObject(new Sprite("DuckSheet2.png", 1, 1, 13, 14));
						obj->Position(Vector2{ (float)(i * 100), (float)( j * 100) });
						obj->Active(false);
					}
				}
			}

			

			if (mInputMgr->GetKeyDown(SDL_SCANCODE_F))
			{
				mSceneMgr->GetScene()->ClearScene();
			}
			

			if (mInputMgr->GetKey(SDL_SCANCODE_Z))
			{
				camRect.w = camRect.w + 5;
				camRect.h = camRect.h + 5;
			}
			if (mInputMgr->GetKey(SDL_SCANCODE_X))
			{
				camRect.w = camRect.w - 5;
				camRect.h = camRect.h - 5;
			}

			if (mInputMgr->GetKey(SDL_SCANCODE_LEFT))
			{
				camRect.x += 20;
			}
			if (mInputMgr->GetKey(SDL_SCANCODE_RIGHT))
			{
				camRect.x -= 20;
				if (camRect.x < -1920)
					camRect.x = -1920;
			}
			if (mInputMgr->GetKey(SDL_SCANCODE_UP))
			{
				camRect.y += 20;
				if (camRect.y > 0)
					camRect.y = 0;
			}
			if (mInputMgr->GetKey(SDL_SCANCODE_DOWN))
			{
				camRect.y -= 20;
				if (camRect.y < -1080)
					camRect.y = -1080;
			}
			//Graphics::Instance()->SetViewport(&camRect);

			

			//Update Calls
			mSceneMgr->GetScene()->Update();

			//mTex->Update();
			//sprite->Update();
			// 
			
			//Tex Update Calls
			mSceneMgr->GetScene()->UpdateTextures();
			//mTex->UpdateTexture();
			//sprite->UpdateTexture();

			//Draw Calls
			mSceneMgr->GetScene()->Render();
			//mTex->Render();
			//sprite->Render();
			//text->Render();q

			mGraphics->Render();

			
			mInputMgr->UpdatePrevInput();

			mTimer->Reset();
		}


	}
}