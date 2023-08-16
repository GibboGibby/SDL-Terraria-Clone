#pragma once

#include "Collider.h"

class CircleCollider : public Collider {

private:
	float radius;

public:
	CircleCollider(float radius, bool broadPhase = false);
	~CircleCollider()

};