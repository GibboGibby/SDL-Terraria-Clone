#include "Timer.h"

Timer* Timer::instance = NULL;

Timer* Timer::Instance()
{
	if (instance == NULL)
		instance = new Timer();

	return instance;
}

void Timer::Release()
{
	delete instance;
	instance = NULL;
}

Timer::Timer()
{
	Reset();
	mTimeScale = 1.0f;
}

Timer::~Timer()
{

}

void Timer::Reset()
{
	mStartTicks = SDL_GetTicks();
	mElapsedTicks = 0;
	mDeltaTime = 0.0f;
}

float Timer::DeltaTime()
{
	return mDeltaTime;
}

void Timer::TimeScale(float scale)
{
	mTimeScale = scale;
}

float Timer::TimeScale()
{
	return mTimeScale;
}

void Timer::Update()
{
	mElapsedTicks = SDL_GetTicks() - mStartTicks;
	mDeltaTime = mElapsedTicks * 0.001f;
}