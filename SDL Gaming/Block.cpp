#include "Block.h"

Block::Block(BlockType type)
{
	//sprite = new Sprite("dirt-full.png");
	

	
	switch (type)
	{
	case Dirt:
		sprite = new Sprite("dirt-full.png");
		break;
	case Cobble:
		sprite = new Sprite("stone-full.png");
		break;
	case Iron:
		break;
	default:
		sprite = new Sprite("dirt.png");
		break;
	}

	//sprite->Name("BlockName");
	sprite->Position(VEC2_ZERO);
	sprite->Parent(this);

	
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