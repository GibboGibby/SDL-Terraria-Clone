#pragma once
#include "GameObject.h"

class TestObject : public GameObject
{
private:
	double prevTime = 0;
	double intervalTime = 1. / 60.f;
public:
	TestObject();
	void Start();
	virtual void Update();
	virtual void Render(SDL_Renderer* renderer);
};