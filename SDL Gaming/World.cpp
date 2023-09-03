#include "World.h"

World::World()
{

	distToTopLeft = pow(Graphics::SCREEN_WIDTH / 2, 2) + pow(Graphics::SCREEN_HEIGHT, 2);
	distToTopLeft = sqrt(distToTopLeft);

	startingPos = Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2);

	Block* block = new Block();
	scaledDimensions = block->GetScaledDimensions();

	//Position(SceneManager::Instance()->GetScene()->GetActiveCamera()->Position());

	for (int i = 0; i < XROWS; i++)
	{
		std::vector<Block*> blocksLine;
		for (int j = 0; j < YROWS; j++)
		{
			blocksLine.push_back(nullptr);
		}
		mBlocks.push_back(blocksLine);
	}

	
	for (int i = 0; i < XROWS; i++)
	{
		for (int j = 0; j < YROWS; j++)
		{
			//if (j > 5) continue;
			Block* block = new Block(Dirt);
			mBlocks[i][j] = block;
			block->Parent(this);
			//Vector2 scaledDims = block->GetScaledDimensions();
			block->Position(Vector2(startingPos.x + i * scaledDimensions.x, startingPos.y + j * scaledDimensions.y));
		}
	}
	
	
	/*
	for (int i = 0; i < 10; i++)
	{
		if (i == 5) continue;
		Block* block = new Block(Dirt);
		mBlocks[i][0] = block;
		block->Parent(this);
		Vector2 scaledDims = block->GetScaledDimensions();
		//block->Position(Vector2(i * scaledDims.x, 0 * scaledDims.y));
		block->Position(Vector2(Graphics::SCREEN_WIDTH - 400 + i * scaledDims.x, Graphics::SCREEN_HEIGHT + 400 + 0 * scaledDims.y));
		block->Parent(this);
		Block* block2 = new Block(Dirt);
		mBlocks[i][1] = block2;
		block2->Parent(this);
		block2->Position(Vector2(Graphics::SCREEN_WIDTH - 400 + i * scaledDims.x, Graphics::SCREEN_HEIGHT + 400 + 1 * scaledDims.y));
		//obj4->Position(Vector2(Graphics::SCREEN_WIDTH - 400, Graphics::SCREEN_HEIGHT - 400));

	}

	mBlocks[100][100] = new Block();
	mBlocks[100][100]->Position(Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT));
	mBlocks[100][100]->Name("BlockName");

	*/
}

World::~World()
{
	for (int i = 0; i < XROWS; i++)
	{
		for (int j = 0; j < YROWS; j++)
		{
			delete mBlocks[i][j];
		}
	}
}

void World::Render()
{
	//mBlocks[100][100]->Render();
	
	for (int i = 0; i < XROWS; i++)
	{
		for (int j = 0; j < YROWS; j++)
		{
			if (mBlocks[i][j] == nullptr)
				continue;

			
			if ((mBlocks[i][j]->Position() - SceneManager::Instance()->GetScene()->GetActiveCamera()->Position()).Magnitude() > distToTopLeft * 2) 
				mBlocks[i][j]->Active(false);
			else
				mBlocks[i][j]->Active(true);

			if (mBlocks[i][j]->Active())
				mBlocks[i][j]->Render();


			//mBlocks[i][j]->blockSprite->Render();
		}
	}
	
}

void World::Update()
{
	if (Input->GetKeyDown(SDL_SCANCODE_M))
	{
		Position(SceneManager::Instance()->GetScene()->ScreenToWorldPosition(Input->GetMousePos()));
	}

	if (Input->GetMouseButton(Input->LEFT))
	{
		//Vector2 start = CurrentScene->WorldToScreenPosition(startingPos);

		Vector2 mouseWorldPos = CurrentScene->ScreenToWorldPosition(Input->GetMousePos());
		Vector2 relativeClickPos = mouseWorldPos - startingPos + scaledDimensions / 2;

		int x = relativeClickPos.x / scaledDimensions.x;
		int y = relativeClickPos.y / scaledDimensions.y;

		if ((x >= 0 && x <= XROWS) && (y >= 0 && y <= YROWS))

		if (mBlocks[x][y] != nullptr)
		{
			delete mBlocks[x][y];
			mBlocks[x][y] = nullptr;
		}
	}

	if (Input->GetMouseButton(Input->RIGHT))
	{
		Vector2 mouseWorldPos = CurrentScene->ScreenToWorldPosition(Input->GetMousePos());
		Vector2 relativeClickPos = mouseWorldPos - startingPos + scaledDimensions / 2;

		int x = relativeClickPos.x / scaledDimensions.x;
		int y = relativeClickPos.y / scaledDimensions.y;

		if ((x >= 0 && x <= XROWS) && (y >= 0 && y <= YROWS))

		if (mBlocks[x][y] == nullptr)
		{
			mBlocks[x][y] = new Block();
			mBlocks[x][y]->Parent(this);
			mBlocks[x][y]->Position(Vector2(startingPos.x + x * scaledDimensions.x, startingPos.y + y * scaledDimensions.y));
		}
	}

	
}

void World::Serialize()
{

}

void World::DeSerialize()
{

}
void World::Awake()
{

}

void World::Start()
{

}

void World::FixedUpdate()
{

}

void World::LateUpdate()
{

}

void World::UpdateTexture()
{

}