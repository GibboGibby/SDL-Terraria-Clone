#include "PhysicsEntity.h"
#include "CircleCollider.h"

PhysicsEntity::PhysicsEntity()
{
	mBroadPhaseCollider = nullptr;
}

PhysicsEntity::~PhysicsEntity()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		delete mColliders[i];
		mColliders[i] = nullptr;
	}

	mColliders.clear();

	if (mBroadPhaseCollider)
	{
		delete mBroadPhaseCollider;
		mBroadPhaseCollider = nullptr;
	}
}



void PhysicsEntity::AddCollider(Collider* collider, Vector2 localPos)
{
	collider->Parent(this);
	collider->Position(localPos);
	mColliders.push_back(collider);

	if (mColliders.size() > 1 || mColliders[0]->GetType() != Collider::ColliderType::Circle)
	{
		float furthestDist = mColliders[0]->GetFurthestPoint().Magnitude();
		float dist = 0.0f;
		for (int i = 1; i < mColliders.size(); i++)
		{
			dist = mColliders[i]->GetFurthestPoint().Magnitude();
			if (dist > furthestDist)
				furthestDist = dist;
		}
		delete mBroadPhaseCollider;
		mBroadPhaseCollider = new CircleCollider(furthestDist, true);
		mBroadPhaseCollider->Parent(this);
		mBroadPhaseCollider->Position(VEC2_ZERO);
	}

}


void PhysicsEntity::Render()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		mColliders[i]->Render();
	}

	if (mBroadPhaseCollider)
		mBroadPhaseCollider->Render();
}

void PhysicsEntity::Awake()
{

}

void PhysicsEntity::Start()
{

}

void PhysicsEntity::Update()
{

}

void PhysicsEntity::UpdateTexture()
{

}