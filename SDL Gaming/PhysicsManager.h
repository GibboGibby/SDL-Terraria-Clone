#pragma once

#include "PhysicsEntity.h"
#include "Timer.h"
#include <bitset>
#define PIXELS_PER_METRE 8

class PhysicsManager
{
public:

	struct PhysicsSettings
	{
		float gravity = -20.f;
	};

	
	PhysicsSettings physicsSettings;

	enum class CollisionLayers
	{
		Friendly,
		FriendlyProjectiles,
		Enemy,
		EnemyProjectiles,
		Environment,
		//
		MaxLayers
	};

	enum class CollisionFlags
	{
		None = 0x00,
		Friendly = 0x01,
		FriendlyProjectiels = 0x02,
		Enemy = 0x04,
		EnemyProjectiles = 0x08,
		Environment = 0x16
	};

private:
	static PhysicsManager* instance;

	PhysicsSettings physSettings;
	std::vector<PhysicsEntity*> mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
	std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

	unsigned long mLastId;

	void ResolveCollision(const Manifold& m);


	void PositionalCorrection(const Manifold& m);

	void ApplyDrag(RigidBody& entity);

public:

	static PhysicsManager* Instance();
	static void Release();

	void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

	unsigned long RegisterEntity(PhysicsEntity* entity, CollisionLayers layer);
	void UnregisterEntity(unsigned long id);

	void CollisionUpdate();
	void PhysicsUpdate();
	bool CollisionCheck(Collider* col);

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