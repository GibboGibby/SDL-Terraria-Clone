#pragma once
#include "SDL.h"

class Timer {
private:
	static Timer* instance;

	unsigned int mStartTicks;
	unsigned int mElapsedTicks;
	unsigned int mPhysicsStartTicks;
	unsigned int mPhysicsElapsedTicks;
	float mDeltaTime;
	float mPhysicsDeltaTime;
	float mTimeScale;

public:

	static Timer* Instance();

	static void Release();

	void Reset();
	void ResetPhysics();
	float DeltaTime();
	float PhysicsDeltaTime();

	void TimeScale(float scale);
	float TimeScale();

	void Update();

private:
	Timer();
	~Timer();
};