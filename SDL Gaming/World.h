#pragma once
#include "ISerialize.h"
#include "Block.h"

#define XROWS 100
#define YROWS 100

class World : public GameObject, ISerializable
{
public:
	World();
	~World();



	void Serialize();
	void DeSerialize();

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void LateUpdate();
	virtual void UpdateTexture();
	virtual void Render();

private:
	
	//Block* mBlocks[256][256] = new Block[256][256];
	std::vector<std::vector<Block*>> mBlocks;

	float distToTopLeft;

	Vector2 startingPos;
	Vector2 scaledDimensions;
};