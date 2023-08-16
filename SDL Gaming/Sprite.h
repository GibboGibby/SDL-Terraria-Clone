#pragma once

#include "GameObject.h"
#include "AssetManager.h"
#include "AudioManager.h"
#include "SceneManager.h"

#define MainCam SceneManager::Instance()->GetScene()->GetActiveCamera()
#define CurrentScene SceneManager::Instance()->GetScene()

enum WRAP_MODE { ONCE = 0, LOOP = 1 };
enum ANIM_DIR { HORIZONTAL = 0, VERTICAL = 1 };

class Animation {

public:
	int StartX;
	int StartY;

	float AnimationTimer;
	float AnimationSpeed;
	float TimePerFrame;

	int FrameCount;

	WRAP_MODE WrapMode;
	ANIM_DIR AnimDir;

public:
	/// <summary>
	/// Creates the Animation Class
	/// </summary>
	/// <param name="x">x val</param>
	/// <param name="y">y val</param>
	/// <param name="speed">animation speed</param>
	/// <param name="frameCount">frame count</param>
	/// <param name="wrapMode">wrap mode</param>
	/// <param name="dir">direction</param>
	Animation(int x, int y, float speed, int frameCount, WRAP_MODE wrapMode = LOOP, ANIM_DIR dir = HORIZONTAL)
	{
		StartX = x;
		StartY = y;
		AnimationTimer = 0.0f;
		AnimationSpeed = speed;
		FrameCount = frameCount;
		TimePerFrame = speed / frameCount;

		AnimDir = dir;
		WrapMode = wrapMode;
	}
};

class Sprite : public GameObject
{
protected:
	SDL_Texture* mTex;
	Graphics* mGraphics;

	Timer* mTimer;

	bool mClipped;
	SDL_Rect mClipRect;

	bool spriteFlipped = false;

	bool customCenter;
	SDL_Point* centerPos;

	float mAnimationTimer = 0.0f;

	SDL_Rect mRenderRect;

	std::map<std::string, Animation*> mAnimations;

	Animation* currentAnimation = NULL;
	Animation* prevAnimation = NULL;



public:
	Sprite(std::string file);
	Sprite(std::string file, int x, int y, int w, int h, int custX = 0, int custY = 0);
	Sprite(std::string text, std::string fontPath, int size, SDL_Color color);
	~Sprite();

	void SpriteFlipped(bool val) { spriteFlipped = val; }

	virtual void Update();
	virtual void Render();

	Vector2 ScaledDimensions();

	void UpdateTexture();

	void AddAnimation(std::string animName, Animation* animation);
	void ChangeAnimation(std::string animName);
	std::string GetCurrentAnimation();
	std::vector<std::string> ReturnListOfAnimations();
};