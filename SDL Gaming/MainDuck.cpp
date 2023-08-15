#include "Duck.h"
#include "BoxCollider.h"

MainDuck::MainDuck()
{
	sprite = new Sprite("DuckSheet2.png", 1, 1, 13, 14);
	sprite->Name("Main Character");
	sprite->Parent(this);
	sprite->Scale(Vector2(10.f, 10.f));

	AddCollider(new BoxCollider(sprite->ScaledDimensions()));
	
}

MainDuck::~MainDuck()
{
	delete sprite;
	sprite = NULL;
}

void MainDuck::Awake()
{

}

void MainDuck::Start()
{
}

void MainDuck::Update()
{
	//sprite->Update();

	if (!Active()) return;

	if (Input->GetKey(SDL_SCANCODE_D))
	{
		Translate(Vector2(100.f, 0.0f) * deltaTime);
	}
	
	Vector2 prevScale = Scale();
	if (Input->GetKey(SDL_SCANCODE_UP))
	{
		Scale(Vector2(prevScale.x, prevScale.y + 5.f * deltaTime));
	}
	if (Input->GetKey(SDL_SCANCODE_DOWN))
	{
		Scale(Vector2(prevScale.x, prevScale.y - 5.f * deltaTime));
	}
	if (Input->GetKey(SDL_SCANCODE_LEFT))
	{
		Scale(Vector2(prevScale.x - 5.f * deltaTime, prevScale.y));
	}
	if (Input->GetKey(SDL_SCANCODE_RIGHT))
	{
		Scale(Vector2(prevScale.x + 5.f * deltaTime, prevScale.y));
	}

	if (Input->GetKeyDown(SDL_SCANCODE_RETURN))
	{
		cameraFollow = !cameraFollow;
	}

	if (cameraFollow)
	{
		MainCam->Position(Position());
	}

	if (Input->GetKeyDown(SDL_SCANCODE_Q))
	{
		AudioManager::Instance()->PlaySFX("quack.wav");
	}

	if (Input->GetMouseButton(InputManager::LEFT))
	{
		//Position(Input->GetMousePos());
		Position(CurrentScene->ScreenToWorldPosition(Input->GetMousePos()));
	}

	if (Input->GetKeyDown(SDL_SCANCODE_A))
	{
		sprite->SpriteFlipped(true);
	}
	else if (Input->GetKeyDown(SDL_SCANCODE_D))
	{
		sprite->SpriteFlipped(false);
	}

	if (Input->GetKeyUp(SDL_SCANCODE_D))
	{
		if (Input->GetKey(SDL_SCANCODE_A))
		{
			sprite->SpriteFlipped(true);
		}
	}

	if (Input->GetKeyUp(SDL_SCANCODE_A))
	{
		if (Input->GetKey(SDL_SCANCODE_D))
		{
			sprite->SpriteFlipped(false);
		}
	}

	if (Input->GetKey(SDL_SCANCODE_A))
	{
		Translate(Vector2(-1000.f, 0.f) * deltaTime);
	}
	if (Input->GetKey(SDL_SCANCODE_D))
		Translate(Vector2(1000.f, 0.f) * deltaTime);
	if (Input->GetKey(SDL_SCANCODE_W))
		Translate(Vector2(0.f, -1000.f) * deltaTime);
	if (Input->GetKey(SDL_SCANCODE_S))
		Translate(Vector2(0.f, 1000.f) * deltaTime);

	if (Input->GetKeyUp(SDL_SCANCODE_W) || Input->GetKeyUp(SDL_SCANCODE_S) || Input->GetKeyUp(SDL_SCANCODE_A) || Input->GetKeyUp(SDL_SCANCODE_D))
		if (!Input->GetKey(SDL_SCANCODE_W) && !Input->GetKey(SDL_SCANCODE_S) && !Input->GetKey(SDL_SCANCODE_A) && !Input->GetKey(SDL_SCANCODE_D))
		{
			sprite->ChangeAnimation("idle");
		}
	if (Input->GetKeyDown(SDL_SCANCODE_W) || Input->GetKeyDown(SDL_SCANCODE_S) || Input->GetKeyDown(SDL_SCANCODE_A) || Input->GetKeyDown(SDL_SCANCODE_D))
	{
		if (sprite->GetCurrentAnimation() != "walking")
			sprite->ChangeAnimation("walking");
	}
	
}

void MainDuck::UpdateTexture()
{
	sprite->UpdateTexture();
}

void MainDuck::Render()
{
	//if (Active())
	sprite->Render();
	PhysicsEntity::Render();

}