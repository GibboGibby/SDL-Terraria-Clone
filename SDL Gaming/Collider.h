#pragma once
#include "Sprite.h"

class Collider : public GameObject {
public:
	enum class ColliderType
	{
		Box,
		Circle
	};

protected:
	ColliderType mType;
	static const bool DEBUG_COLLIDERS = true;
	Sprite* mDebugTexture;

public:
	Collider(ColliderType type);
	virtual ~Collider();

	virtual void Render();

protected:

	void SetDebugTexture(Sprite* texture);
};