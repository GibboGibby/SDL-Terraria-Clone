#pragma once
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "PointCollider.h"

struct Manifold
{
	Collider* A;
	Collider* B;
	float penetration;
	Vector2 normal;
};

enum ForceMode
{
	Force,
	Acceleration,
	Impulse,
	VelocityChange
};

inline bool AABBvsAABBCollision(Manifold& m)
{
	BoxCollider* A = static_cast<BoxCollider*>(m.A);
	BoxCollider* B = static_cast<BoxCollider*>(m.B);
	
	Vector2 n = B->Position() - A->Position();
	AABB abox = A->GetAABB();
	AABB bbox = B->GetAABB();

	float a_extent = (abox.max.x - abox.min.x) / 2;
	float b_extent = (bbox.max.x - bbox.min.x) / 2;

	float x_overlap = a_extent + b_extent - abs(n.x);

	if (x_overlap > 0)
	{
		float ya_extent = (abox.max.y - abox.min.y) / 2;
		float yb_extent = (bbox.max.y - bbox.min.y) / 2;

		float y_overlap = ya_extent + yb_extent - abs(n.y);
		
		if (y_overlap > 0)
		{
			if (x_overlap < y_overlap)
			{
				if (n.x < 0)
					m.normal = Vector2(1, 0);
				else
					m.normal = Vector2(-1, 0);
				m.penetration = x_overlap;
				return true;
			}
			else
			{
				if (n.y < 0)
					m.normal = Vector2(0, 1);
				else
					m.normal = Vector2(0, -1);
				m.penetration = y_overlap;
				return true;
			}
		}
	}
	return false;
}

inline bool CircleCircleCollision(CircleCollider* c1, CircleCollider* c2)
{
	return (c1->Position() - c2->Position()).Magnitude() < (c1->GetRadius() + c2->GetRadius());
}

inline bool BoxBoxCollision(BoxCollider* c1, BoxCollider* c2)
{
	AABB a = c1->GetAABB();
	AABB b = c2->GetAABB();
	
	if (a.max.x < b.min.x || a.min.x > b.max.x) return false;
	if (a.max.y < b.min.y || a.min.y > b.max.y) return false;

	return true;
}

inline bool BoxPointCollision(BoxCollider* c1, PointCollider* c2)
{
	AABB aabb = c1->GetAABB();
	return (c2->GetFurthestPoint().x > aabb.min.x && c2->GetFurthestPoint().x < aabb.max.x &&
		c2->GetFurthestPoint().y > aabb.min.y && c2->GetFurthestPoint().y < aabb.max.y);
}

inline bool PointBoxCollision(PointCollider* c1, BoxCollider* c2)
{
	return BoxPointCollision(c2, c1);
}

inline bool ColliderColliderCheck(Collider* c1, Collider* c2)
{
	if (c1->GetType() == Collider::ColliderType::Circle && c2->GetType() == Collider::ColliderType::Circle)
		return CircleCircleCollision(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
	if (c1->GetType() == Collider::ColliderType::Box && c2->GetType() == Collider::ColliderType::Box)
		return BoxBoxCollision(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
	if (c1->GetType() == Collider::ColliderType::Box && c2->GetType() == Collider::ColliderType::Circle)
		return false;
	if (c1->GetType() == Collider::ColliderType::Circle && c2->GetType() == Collider::ColliderType::Box)
		return false;
}

inline bool ColliderColliderCheck(Manifold& m)
{
	if (m.A->GetType() == Collider::ColliderType::Box && m.B->GetType() == Collider::ColliderType::Box)
	{
		return AABBvsAABBCollision(m);
		//ResolveCollision(m);
	}
	if (m.A->GetType() == Collider::ColliderType::Box && m.B->GetType() == Collider::ColliderType::Point)
		return BoxPointCollision(static_cast<BoxCollider*>(m.A), static_cast<PointCollider*>(m.B));
	if (m.A->GetType() == Collider::ColliderType::Point && m.B->GetType() == Collider::ColliderType::Box)
		return PointBoxCollision(static_cast<PointCollider*>(m.A), static_cast<BoxCollider*>(m.B));

	
	return false;
}

inline float DragForceMagnitude(Vector2 velocity, float drag)
{
	return velocity.MagnitudeSquared() * drag;
}

inline Vector2 DragForceVector(Vector2 velocity, float drag)
{
	return DragForceMagnitude(velocity, drag) * -velocity.Normalized();
}

inline float min(float a, float b)
{
	return (a < b) ? a : b;
}

inline float max(float a, float b)
{
	return (a < b) ? b : a;
}

//https://gamedevelopment.tutsplus.com/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331t

//https://www.codeproject.com/Articles/1067334/Making-a-D-Physics-Engine-Spaces-and-Bodies