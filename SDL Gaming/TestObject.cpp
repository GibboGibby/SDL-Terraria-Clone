#include "TestObject.h"
#include "Input.h"
#include <random>
#include <iostream>

TestObject::TestObject()
{
	Start();
}

void TestObject::Start()
{
	r.w = 50;
	r.h = 50;
	position.x = rand() % 800;
	position.y = rand() % 600;
	prevTime = SDL_GetTicks();
}

void TestObject::Update()
{

	if (InputManager::Instance()->GetKeyDown(SDL_SCANCODE_W))
	{
		std::cout << "W has been pressed" << std::endl;
	}
	if (Input->GetKeyUp(SDL_SCANCODE_W))
	{
		std::cout << "W key has been released\n";
	}

	if (Input->GetKey(SDL_SCANCODE_W))
	{
		std::cout << "Epic\n";
	}

	if (Input->GetMouseButtonDown(InputManager::LEFT))
	{
		std::cout << "Left Mouse Button Pressed\n";
	}
	if (Input->GetMouseButtonUp(InputManager::LEFT))
	{
		std::cout << "Left Mouse Button Released\n"; 

	if (Input->GetMouseButton(InputManager::RIGHT))
	{
		Vector2 mousePos = Input->GetMousePos();
		position.x = mousePos.x;
		position.y = mousePos.y;
	}

	if (SDL_GetTicks() > prevTime + intervalTime)
	{
		position.y--;
		if (position.y > 600)
			position.y = 0;
		if (position.y < 0)
			position.y = 600;

		r.x = position.x;
		r.y = position.y;
	}
}

void TestObject::Render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 0,0,255,255);

	SDL_RenderDrawRect(renderer, &r);
}