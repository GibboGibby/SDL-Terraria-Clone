#pragma once
#include "PhysicsHelper.h"
#include <vector>

class PhysicsEntity : public GameObject
{
protected:

	unsigned long mId;

	std::vector<Collider*> mColliders;

	
	
	Collider* mBroadPhaseCollider;

public:

	struct RigidBody
	{
		float angularDrag;
		float inv_mass;
		float angularVelocity;
		bool automaticCenterOfMass;
		//bool automaticInertiaTensor;
		Vector2 centerOfMass = VEC2_ZERO;
		bool constraints[2] = {false, false};
		bool detectCollisions;
		bool freezeRotation;
		float mass = 1.0f;
		float maxAngularVelocity = 7;
		float maxLinearVelocity;
		bool isKinematic = true;
		bool isStatic = false;
		bool useGravity = true;
		float restitution = 1.0f;
		Vector2 velocity;
	};

	

	RigidBody rb;

	PhysicsEntity();
	virtual ~PhysicsEntity();

	unsigned long GetID();

	bool CheckCollision(PhysicsEntity* other, Manifold& m);

	//bool CheckCollision(PhysicsEntity* other);

	virtual void Hit(PhysicsEntity* other);

	virtual void OnCollisionEnter(PhysicsEntity* other);

	

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void UpdateTexture();
	virtual void Render();

protected:
	virtual bool IgnoreCollision();
	void AddCollider(Collider* collider, Vector2 localPos = VEC2_ZERO);
};