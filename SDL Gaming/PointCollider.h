#pragma once
#include "Collider.h"

class PointCollider : public Collider
{
private:
	Vector2 pointPos;
public:
	PointCollider(Vector2 position);
	~PointCollider();

	Vector2 GetFurthestPoint() override;
};