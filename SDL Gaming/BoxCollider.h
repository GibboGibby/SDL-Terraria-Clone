#pragma once

#include "Collider.h"

class BoxCollider : public Collider
{
private:
	static const int MAX_VERTS = 4;
	GameObject* mVerts[MAX_VERTS];

public:
	BoxCollider(Vector2 size);
	~BoxCollider();

private:
	void AddVert(int index, Vector2 pos);
};