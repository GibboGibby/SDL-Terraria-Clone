#pragma once
#include "CircleCollider.h"
#include "BoxCollider.h"

inline bool CircleCircleCollision(CircleCollider* c1, CircleCollider* c2)
{
	return (c1->Position() - c2->Position()).Magnitude() < (c1->GetRadius() + c2->GetRadius());
}

inline bool ColliderColliderCheck(Collider* c1, Collider* c2)
{
	if (c1->GetType() == Collider::ColliderType::Circle && c2->GetType() == Collider::ColliderType::Circle)
		return CircleCircleCollision(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
}

inline float DragForceMagnitude(Vector2 velocity, float drag)
{
	return velocity.MagnitudeSquared() * drag;
}

inline Vector2 DragForceVector(Vector2 velocity, float drag)
{
	return DragForceMagnitude(velocity, drag) * -velocity.Normalized();
}

//https://gamedevelopment.tutsplus.com/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331t

//https://www.codeproject.com/Articles/1067334/Making-a-D-Physics-Engine-Spaces-and-Bodies