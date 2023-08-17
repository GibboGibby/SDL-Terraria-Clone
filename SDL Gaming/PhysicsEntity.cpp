#include "PhysicsEntity.h"


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



bool PhysicsEntity::IgnoreCollision()
{
	return false;
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

unsigned long PhysicsEntity::GetID()
{
	return mId;
}

bool PhysicsEntity::CheckCollision(PhysicsEntity* other)
{
	return ColliderColliderCheck(mBroadPhaseCollider, other->mBroadPhaseCollider);
}

void PhysicsEntity::Hit(PhysicsEntity* other)
{
	
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