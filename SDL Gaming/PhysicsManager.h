#pragma once

#include "PhysicsEntity.h"
#include "Timer.h"
#include <bitset>

class PhysicsManager
{
public:

	struct PhysicsSettings
	{
		float gravity = -9.8f;
	};


	enum class CollisionLayers
	{
		Friendly,
		FriendlyProjectiles,
		Enemy,
		EnemyProjectiles,
		//
		MaxLayers
	};

	enum class CollisionFlags
	{
		None = 0x00,
		Friendly = 0x01,
		FriendlyProjectiels = 0x02,
		Enemy = 0x04,
		EnemyProjectiles = 0x08
	};

private:
	static PhysicsManager* instance;

	PhysicsSettings physSettings;
	std::vector<PhysicsEntity*> mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
	std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

	unsigned long mLastId;

	void ResolveCollision(PhysicsEntity* entity1, AABB entity1aabb, PhysicsEntity* entity2, AABB entity2aabb);
	void ResolveCollision(BoxCollider* col1, BoxCollider* col2);
	void ResolveCollision(CircleCollider* col1, CircleCollider* col2);

public:

	static PhysicsManager* Instance();
	static void Release();

	void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

	unsigned long RegisterEntity(PhysicsEntity* entity, CollisionLayers layer);
	void UnregisterEntity(unsigned long id);

	void CollisionUpdate();
	void PhysicsUpdate();

private:

	PhysicsManager();
	~PhysicsManager();
};

inline PhysicsManager::CollisionFlags operator|(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b)
{
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline PhysicsManager::CollisionFlags operator&(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b)
{
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}