#include "PhysicsEntity.h"
#include "MathsHelper.h"
#include "ExtraPhysics.h"

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

bool PhysicsEntity::CheckCollision(PhysicsEntity* other, Manifold& m)
{
	//return ColliderColliderCheck(mBroadPhaseCollider, other->mBroadPhaseCollider);
	if (mColliders.size() != 0)
	{
		for (Collider* collider : mColliders)
		{
			//ColliderColliderCheck(collider, other->mColliders[0]);
			for (int i = 0; i < other->mColliders.size(); i++)
			{
				//Manifold* m = new Manifold();
				m.A = collider;
				m.B = other->mColliders[i];
				return ColliderColliderCheck(m);
			}
		}
	}
}

bool PhysicsEntity::CheckCollision(Collider* other, Manifold& m)
{
	//return ColliderColliderCheck(mBroadPhaseCollider, other->mBroadPhaseCollider);
	if (mColliders.size() != 0)
	{
		for (Collider* collider : mColliders)
		{
			//ColliderColliderCheck(collider, other->mColliders[0]);
				//Manifold* m = new Manifold();
			m.A = collider;
			m.B = other;
			return ColliderColliderCheck(m);
		}
	}
}

void PhysicsEntity::Hit(PhysicsEntity* other)
{
	
}

void PhysicsEntity::OnCollisionEnter(PhysicsEntity* other)
{

}

bool PhysicsEntity::Raycast(Vector2 origin, Vector2 direction, float distance)
{
	return Physics::Raycast(origin, direction, distance, this);
}

void PhysicsEntity::AddForce(Vector2 force, ForceMode mode)
{
	switch (mode)
	{
	case Force:
		break;
	case Acceleration:
		break;
	case Impulse:
		break;
	case VelocityChange:
		break;
	} 
}

void PhysicsEntity::AddForce(Vector2 velocity)
{
	velocity.y = -velocity.y;
	rb.velocity += velocity;
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