#pragma once
#include "PhysicsHelper.h"
#include <vector>

struct RigidBody
{
	float angularDrag;
	float inv_mass;
	float angularVelocity;
	bool automaticCenterOfMass;
	//bool automaticInertiaTensor;
	Vector2 centerOfMass = VEC2_ZERO;
	bool constraints[2] = { false, false };
	bool detectCollisions;
	bool freezeRotation;
	float mass = 1.0f;
	float drag = 0.25f;
	float friction = 0.35f;
	float maxAngularVelocity = 7;
	Vec2 maxLinearVelocity = {-1,-1};
	bool isKinematic = true;
	bool isStatic = false;
	bool useGravity = true;
	float restitution = 1.0f;
	Vector2 velocity;
	Vector2 acceleration = VEC2_ZERO;
};


class PhysicsEntity : public GameObject
{
protected:

	unsigned long mId;

	std::vector<Collider*> mColliders;

	
	
	Collider* mBroadPhaseCollider;

public:

	RigidBody rb;

	PhysicsEntity();
	virtual ~PhysicsEntity();

	unsigned long GetID();

	bool CheckCollision(PhysicsEntity* other, Manifold& m);

	//bool CheckCollision(PhysicsEntity* other);

	virtual void Hit(PhysicsEntity* other);

	virtual void OnCollisionEnter(PhysicsEntity* other);

	void AddForce(Vector2 force, ForceMode mode);
	void AddForce(Vector2 velocity);

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void UpdateTexture();
	virtual void Render();

protected:
	virtual bool IgnoreCollision();
	void AddCollider(Collider* collider, Vector2 localPos = VEC2_ZERO);
};