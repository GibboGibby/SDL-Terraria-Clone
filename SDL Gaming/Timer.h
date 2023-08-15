#pragma once
#include "SDL.h"

class Timer {
private:
	static Timer* instance;

	unsigned int mStartTicks;
	unsigned int mElapsedTicks;
	float mDeltaTime;
	float mTimeScale;

public:

	static Timer* Instance();

	static void Release();

	void Reset();
	float DeltaTime();

	void TimeScale(float scale);
	float TimeScale();

	void Update();

private:
	Timer();
	~Timer();
};