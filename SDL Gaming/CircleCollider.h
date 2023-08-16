#pragma once

#include "Collider.h"

class CircleCollider : public Collider {

private:
	float radius;

public:
	CircleCollider(float _radius, bool broadPhase = false);
	~CircleCollider();
	
	Vector2 GetFurthestPoint() override;
};