#include "Block.h"

Block::Block(BlockType type)
{
	sprite = new Sprite("dirt-full.png");
	sprite->Name("BlockName");
	sprite->Position(VEC2_ZERO);
	sprite->Parent(this);

	/*
	switch (type)
	{
	case Dirt:
		blockSprite = new Sprite("dirt.png");
		break;
	case Cobble:
		break;
	case Iron:
		break;
	default:
		blockSprite = new Sprite("dirt.png");
		break;
	}

	*/
	AddCollider(new BoxCollider(sprite->ScaledDimensions()));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Environment);

	rb.isStatic = true;
}

Block::~Block()
{
	delete sprite;
	sprite == NULL;

	if (mId != 0)
	{
		PhysicsManager::Instance()->UnregisterEntity(mId);
	}
}

void Block::Render()
{
	//blockSprite->Render();
	sprite->Render();
	//PhysicsEntity::Render();
}