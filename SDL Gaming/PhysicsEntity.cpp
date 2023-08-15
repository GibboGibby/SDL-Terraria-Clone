#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity()
{

}

PhysicsEntity::~PhysicsEntity()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		delete mColliders[i];
		mColliders[i] = nullptr;
	}

	mColliders.clear();
}



void PhysicsEntity::AddCollider(Collider* collider, Vector2 localPos)
{
	collider->Parent(this);
	collider->Position(localPos);
	mColliders.push_back(collider);
}


void PhysicsEntity::Render()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		mColliders[i]->Render();
	}
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