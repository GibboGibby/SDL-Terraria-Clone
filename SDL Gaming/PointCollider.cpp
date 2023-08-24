#include "PointCollider.h"

PointCollider::PointCollider(Vector2 position) : Collider(ColliderType::Point)
{
	pointPos = position;

	if (DEBUG_COLLIDERS)
	{
		//Graphics::DrawPoint(position)
	}
}

PointCollider::~PointCollider()
{
}

Vector2 PointCollider::GetFurthestPoint()
{
	return pointPos;
}

