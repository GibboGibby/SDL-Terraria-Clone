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

void PhysicsManager::ResolveCollision(const Manifold& m)
{
	PhysicsEntity* A = static_cast<PhysicsEntity*>(m.A->Parent());
	PhysicsEntity* B = static_cast<PhysicsEntity*>(m.B->Parent());
	A->rb.inv_mass = (A->rb.mass == 0) ? 0 : 1 / A->rb.mass;
	B->rb.inv_mass = (B->rb.mass == 0) ? 0 : 1 / B->rb.mass;
	Vector2 rv = B->rb.velocity - A->rb.velocity;

	float velAlongNormal = Dot(rv, -m.normal);

	if (velAlongNormal > 0)
		return;

	float e = min(A->rb.restitution, B->rb.restitution);

	float j = -(1 + e) * velAlongNormal;
	j /= 1 / A->rb.mass + 1 / B->rb.mass;

	Vector2 impulse = j * -m.normal;
	float mass_sum = A->rb.mass + B->rb.mass;
	float ratio = A->rb.mass / mass_sum;
	//A->rb.velocity -= ratio * impulse;

	ratio = B->rb.mass / mass_sum;
	//B->rb.velocity += ratio * impulse;
	if (!A->rb.isStatic)
		A->rb.velocity -= A->rb.inv_mass * impulse;
	if (!B->rb.isStatic)
		B->rb.velocity += B->rb.inv_mass * impulse;

	PositionalCorrection(m);
}

void PhysicsManager::PositionalCorrection(const Manifold& m)
{
	PhysicsEntity* A = static_cast<PhysicsEntity*>(m.A->Parent());
	PhysicsEntity* B = static_cast<PhysicsEntity*>(m.B->Parent());

	const float percent = 0.2;
	const float slop = 0.01;
	Vector2 correction = max(m.penetration - slop, 0.0f) / (A->rb.inv_mass + B->rb.inv_mass) * percent * -m.normal;
	if (!A->rb.isStatic)
		A->Position(A->Position() - A->rb.inv_mass * correction);
	if (!B->rb.isStatic)
		B->Position(B->Position() - B->rb.inv_mass * correction);
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
						Manifold m;
						if (mCollisionLayers[i][k]->CheckCollision(mCollisionLayers[j][l], m))
						{
							
							//Run collision thing. might need to put this elsewhere tho
							//printf("A name - %s - B name - %s", m.A->Parent()->Name().c_str(), m.B->Parent()->Name().c_str());
							//printf("Normal direction - x: %F, y: %F \n", m.normal.x, m.normal.y);
							//Normal direction indicates which direction manifold object A should go.
							mCollisionLayers[i][k]->OnCollisionEnter(mCollisionLayers[j][l]);
							mCollisionLayers[j][l]->OnCollisionEnter(mCollisionLayers[i][k]);
							ResolveCollision(m);
							//ResolveCollision(mCollisionLayers[i][k], mCollisionLayers[j][l]);
						}
					}
				}
			}
		}
	}
}

void PhysicsManager::ApplyForces(PhysicsEntity* entity)
{

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