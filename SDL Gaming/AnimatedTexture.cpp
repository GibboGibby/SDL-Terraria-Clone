#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(std::string file, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animDir) : Texture(file, x, y, w, h)
{
	mTimer = Timer::Instance();

	mStartX = x;
	mStartY = y;

	mFrameCount = frameCount;
	mAnimationSpeed = animationSpeed;
	mTimerPerFrame = animationSpeed / frameCount;
	mAnimationTimer = 0.0f;

	mAnimDir = animDir;

	mAnimationDone = false;

	mWrapMode = LOOP;
}

AnimatedTexture::~AnimatedTexture()
{
	//Does something
}

void AnimatedTexture::WrapMode(WRAP_MODE mode)
{
	mWrapMode = mode;
}

void AnimatedTexture::UpdateTexture()
{
	if (!mAnimationDone)
	{
		mAnimationTimer += mTimer->DeltaTime();

		if (mAnimationTimer >= mAnimationSpeed)
		{
			if (mWrapMode == LOOP)
			{
				mAnimationTimer -= mAnimationSpeed;
			}
			else
			{
				mAnimationDone = true;
				mAnimationTimer = mAnimationSpeed - mTimerPerFrame;
			}
		}

		if (mAnimDir == HORIZONTAL)
		{
			mClipRect.x = mStartX + (int)(mAnimationTimer / mTimerPerFrame) * mWidth;
		}
		else {
			mClipRect.y = mStartY + (int)(mAnimationTimer / mTimerPerFrame) * mHeight;
		}

	}
}