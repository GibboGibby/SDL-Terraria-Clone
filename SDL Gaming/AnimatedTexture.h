#pragma once


#include "Texture.h"

class AnimatedTexture : public Texture {
public:

	enum WRAP_MODE { ONCE = 0, LOOP = 1};
	enum ANIM_DIR {HORIZONTAL = 0, VERTICAL = 1};

private:
	Timer* mTimer;

	int mStartX;
	int mStartY;

	float mAnimationTimer;
	float mAnimationSpeed;
	float mTimerPerFrame;

	int mFrameCount;

	WRAP_MODE mWrapMode;
	ANIM_DIR mAnimDir;

	bool mAnimationDone;

public:

	AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animDir);
	~AnimatedTexture();

	void WrapMode(WRAP_MODE mode);

	void UpdateTexture();
};