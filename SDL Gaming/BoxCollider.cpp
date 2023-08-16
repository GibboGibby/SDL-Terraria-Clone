#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2 size)
	: Collider(ColliderType::Box)
{
	AddVert(0, Vector2(-0.5f * size.x, -0.5f * size.y));
	AddVert(1, Vector2(0.5f * size.x, -0.5f * size.y));
	AddVert(2, Vector2(-0.5f * size.x, 0.5f * size.y));
	AddVert(3, Vector2(0.5f * size.x, 0.5f * size.y));

	if (DEBUG_COLLIDERS)
	{
		SetDebugTexture(new Sprite("BoxCollider.png"));
		mDebugTexture->Scale(size / 100.0f);
	}
}

BoxCollider::~BoxCollider()
{
	for (int i = 0; i < MAX_VERTS; i++)
	{
		delete mVerts[i];
		mVerts[i] = nullptr;
	}
}

void BoxCollider::AddVert(int index, Vector2 pos)
{
	mVerts[index] = new GameObject(pos);
	mVerts[index]->Parent(this);
}

Vector2 BoxCollider::GetFurthestPoint()
{
	Vector2 localPos = Position(LOCAL);
	int furthestIndex = 0;
	float dist = (localPos + mVerts[0]->Position(LOCAL)).MagnitudeSquared();
	float otherDist = 0.0f;

	for (int i = 1; i < MAX_VERTS; i++)
	{
		otherDist = (localPos + mVerts[i]->Position(LOCAL)).MagnitudeSquared();
		if (otherDist > dist) {
			furthestIndex = i;
			dist = otherDist;
		}
	}

	return localPos + mVerts[furthestIndex]->Position(LOCAL);
}