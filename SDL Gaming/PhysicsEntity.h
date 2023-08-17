#pragma once
#include "PhysicsHelper.h"
#include <vector>

class PhysicsEntity : public GameObject
{
protected:

	unsigned long mId;

	std::vector<Collider*> mColliders;

	
	
	Collider* mBroadPhaseCollider;

public:
	PhysicsEntity();
	virtual ~PhysicsEntity();

	unsigned long GetID();

	bool CheckCollision(PhysicsEntity* other);

	virtual void Hit(PhysicsEntity* other);

	Vector2 velocity;

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void UpdateTexture();
	virtual void Render();

protected:
	virtual bool IgnoreCollision();
	void AddCollider(Collider* collider, Vector2 localPos = VEC2_ZERO);
};