#pragma once
#include "Collider.h"
#include <vector>

class PhysicsEntity : public GameObject
{
protected:
	std::vector<Collider*> mColliders;
	
	Collider* mBroadPhaseCollider;

public:
	PhysicsEntity();
	virtual ~PhysicsEntity();

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void UpdateTexture();
	virtual void Render();

protected:
	void AddCollider(Collider* collider, Vector2 localPos = VEC2_ZERO);
};