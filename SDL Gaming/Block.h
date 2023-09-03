#pragma once
#include "PhysicsEntity.h"
#include "PhysicsManager.h"

enum BlockType
{
	Dirt = 0,
	Cobble,
	Iron
};

class Block : public PhysicsEntity
{
public:
	Block(BlockType type = Dirt);
	~Block();

	virtual void Render();

	Sprite* sprite;
	Vector2 GetScaledDimensions() { return sprite->ScaledDimensions(); }
private:
};