#pragma once
#include "PhysicsEntity.h"
#include "BoxCollider.h"
#include "Sprite.h"
#include "PhysicsManager.h"


class MainDuck : public PhysicsEntity
{

private:
	Sprite* sprite;

	bool cameraFollow = false;

public:
	MainDuck(bool enemy = false);
	~MainDuck();

	virtual void Hit(PhysicsEntity* other);

	virtual void OnCollisionEnter(PhysicsEntity* other);

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void UpdateTexture();
	virtual void Render();
};