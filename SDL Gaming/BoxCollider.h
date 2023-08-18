#pragma once

#include "Collider.h"

struct AABB
{
	Vector2 min;
	Vector2 max;
};

class BoxCollider : public Collider
{
private:
	static const int MAX_VERTS = 4;
	GameObject* mVerts[MAX_VERTS];
	Vector2 mSize;

public:
	BoxCollider(Vector2 size);
	~BoxCollider();

	AABB GetAABB();

	Vector2 GetFurthestPoint() override;

private:
	void AddVert(int index, Vector2 pos);
};