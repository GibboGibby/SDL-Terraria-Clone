#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::instance = nullptr;

PhysicsManager* PhysicsManager::Instance()
{
	if (instance == nullptr)
		instance = new PhysicsManager();

	return instance;
}

void PhysicsManager::Release()
{
	delete instance;
	instance = nullptr;
}

void PhysicsManager::SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags)
{
	mLayerMasks[static_cast<unsigned int>(layer)] = std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)>(static_cast<unsigned int>(flags));
}

unsigned long PhysicsManager::RegisterEntity(PhysicsEntity* entity, CollisionLayers layer)
{
	mCollisionLayers[static_cast<unsigned int>(layer)].push_back(entity);
	mLastId++;

	return mLastId;
}

void PhysicsManager::UnregisterEntity(unsigned long id)
{
	bool found = false;
	for (int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers) && !found; i++)
	{
		for (int j = 0; j < mCollisionLayers[i].size() && !found; j++)
		{
			if (mCollisionLayers[i][j]->GetID() == id)
			{
				mCollisionLayers[i].erase(mCollisionLayers[i].begin() + j);
				found = true;
			}
		}
	}
}

PhysicsManager::PhysicsManager()
{
	mLastId = 0;

	for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers);i++)
	{
		mLayerMasks[i] = std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)>(static_cast<unsigned int>(CollisionFlags::None));
	}
}

PhysicsManager::~PhysicsManager()
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++)
	{
		mCollisionLayers[i].clear();
	}
}

void PhysicsManager::ResolveCollision(PhysicsEntity* entity1, AABB entity1aabb, PhysicsEntity* entity2, AABB entity2aabb)
{
	Vector2 resultantVelocity = entity1->rb.velocity - entity2->rb.velocity;

	

	Vector2 impulseNormal;

	float velAlongNormal = Dot(resultantVelocity, entity1->rb.velocity.Normalized());

	if (velAlongNormal > 0) return;

	//float e = min(entity1->rb.)
}

void PhysicsManager::ResolveCollision(BoxCollider* col1, BoxCollider* col2)
{

}

void PhysicsManager::ResolveCollision(CircleCollider* col1, CircleCollider* col2)
{
	PhysicsEntity* entity1 = static_cast<PhysicsEntity*>(col1->Parent());
	PhysicsEntity* entity2 = static_cast<PhysicsEntity*>(col2->Parent());

	Vector2 resultantVector = entity2->rb.velocity - entity1->rb.velocity;
	Vector2	normal = resultantVector.Normalized();

	float vecAlongNormal = Dot(resultantVector, normal);
	if (vecAlongNormal > 0) return;

	float e = min(entity1->rb.restitution, entity2->rb.restitution);

	float j = -(1 + e) * vecAlongNormal;
	j /= 1 / entity1->rb.mass + 1 / entity2->rb.mass;

	//Apply impulses

	Vector2 impulse = j * normal;
	entity1->rb.velocity -= 1 / entity1->rb.mass * impulse;
	entity2->rb.velocity += 1 / entity2->rb.mass * impulse;
}

void PhysicsManager::CollisionUpdate()
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++)
	{
		for (unsigned int j = 0; j < static_cast<unsigned int>(CollisionLayers::MaxLayers); j++)
		{
			if (mLayerMasks[i].test(j) && i <= j)
			{
				for (unsigned int k = 0; k < mCollisionLayers[i].size(); k++)
				{
					for (unsigned int l = 0; l < mCollisionLayers[j].size(); l++)
					{
						if (mCollisionLayers[i][k]->CheckCollision(mCollisionLayers[j][l]))
						{
							//Run collision thing. might need to put this elsewhere tho
							//ResolveCollision(mCollisionLayers[i][k]->)
							mCollisionLayers[i][k]->OnCollisionEnter(mCollisionLayers[j][l]);
							mCollisionLayers[j][l]->OnCollisionEnter(mCollisionLayers[i][k]);
						}
					}
				}
			}
		}
	}
}

void PhysicsManager::PhysicsUpdate()
{
	for (unsigned int i = 0; i < static_cast<unsigned int>(CollisionLayers::MaxLayers); i++)
	{
		for (unsigned int j = 0; j < mCollisionLayers[i].size(); j++)
		{
			mCollisionLayers[i][j]->Position(mCollisionLayers[i][j]->Position() + (mCollisionLayers[i][j]->rb.velocity * Timer::Instance()->PhysicsDeltaTime()));
		}
	}
}