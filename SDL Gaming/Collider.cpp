#include "Collider.h"

Collider::Collider(ColliderType type) 
	: mType(type)
{
	mDebugTexture = nullptr;
}

Collider::~Collider()
{
	if (mDebugTexture)
	{
		delete mDebugTexture;
		mDebugTexture = nullptr;
	}
}

void Collider::SetDebugTexture(Sprite* texture)
{
	delete mDebugTexture;
	mDebugTexture = texture;
	mDebugTexture->Parent(this);
}

Collider::ColliderType Collider::GetType()
{
	return mType;
}

void Collider::Render()
{
	if (DEBUG_COLLIDERS)
	{
		mDebugTexture->Render();
	}
}