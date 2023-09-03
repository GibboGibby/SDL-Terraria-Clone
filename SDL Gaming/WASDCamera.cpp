#include "WASDCamera.h"

void WASDCamera::Awake()
{

}

void WASDCamera::Start()
{

}

void WASDCamera::Update()
{

	float moveSpeedVal = moveSpeed;
	if (Input->GetKey(SDL_SCANCODE_LSHIFT))
	{
		moveSpeedVal = moveSpeed * 3;
	}
	if (Input->GetKey(SDL_SCANCODE_W))
	{
		Position(Position() + Vec2(0.f, -moveSpeedVal) * deltaTime);
	}

	if (Input->GetKey(SDL_SCANCODE_S))
	{
		Position(Position() + Vec2(0.f, moveSpeedVal) * deltaTime);
	}

	if (Input->GetKey(SDL_SCANCODE_A))
	{
		Position(Position() + Vec2(-moveSpeedVal, 0.f) * deltaTime);
	}

	if (Input->GetKey(SDL_SCANCODE_D))
	{
		Position(Position() + Vec2(moveSpeedVal, 0.f) * deltaTime);
	}
}

void WASDCamera::Render()
{

}