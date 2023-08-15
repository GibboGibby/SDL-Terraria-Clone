#pragma once
#include "PhysicsEntity.h"
#include "Sprite.h"


class MainDuck : public PhysicsEntity
{

private:
	Sprite* sprite;

	bool cameraFollow = false;

public:
	MainDuck();
	~MainDuck();

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void UpdateTexture();
	virtual void Render();
};