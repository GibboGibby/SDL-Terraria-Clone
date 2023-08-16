#include "CircleCollider.h"

CircleCollider::CircleCollider(float _radius, bool broadPhase) : Collider(ColliderType::Circle)
{
	radius = _radius;

	if (DEBUG_COLLIDERS)
	{
		if (broadPhase)
			SetDebugTexture(new Sprite("BroadPhaseCollider.png"));
		else
			SetDebugTexture(new Sprite("CircleCollider.png"));

		mDebugTexture->Scale(VEC2_ONE * (radius * 2 / 100.f));
	}
}

CircleCollider::~CircleCollider()
{

}

Vector2 CircleCollider::GetFurthestPoint()
{
	return VEC2_RIGHT * (radius + Position(LOCAL).Magnitude());
}