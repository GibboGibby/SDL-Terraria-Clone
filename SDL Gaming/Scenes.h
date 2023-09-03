#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Texture.h"
#include "Duck.h"
#include "UIButton.h"
#include "World.h"
#include "WASDCamera.h"


class TextScene : public Scene
{
public:
	TextScene() : Scene()
	{
		GameObject* obj = AddObject(new Sprite("New Gaming!", "stocky.ttf", 72, { 0, 0, 255 }));
		obj->Position(Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT));
		obj->Name("Main Character");

		GameObject* uiObj = AddObject(new CustomButton());
		uiObj->Position(Vector2(Graphics::SCREEN_WIDTH + 200, Graphics::SCREEN_HEIGHT + 200));
	}
};

class DuckScene : public Scene
{
public:
	DuckScene()
	{
		//delete activeCamera;
		//activeCamera = NULL;

		activeCamera = new Camera();

		GameObject* obj = AddObject(new MainDuck());
		obj->Position(Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT));
		obj->Name("Main Character");

		/*
		GameObject* obj2 = AddObject(new MainDuck(true));
		obj2->Position(Vector2(Graphics::SCREEN_WIDTH + 200, Graphics::SCREEN_HEIGHT + 200));
		obj2->Name("Main Character Enemy");
		static_cast<PhysicsEntity*>(obj2)->rb.isStatic = true;

		GameObject* obj3 = AddObject(new MainDuck(true));
		obj3->Position(Vector2(Graphics::SCREEN_WIDTH - 200, Graphics::SCREEN_HEIGHT - 200));
		obj3->Name("Main Character Other Enemy");

		*/
		//GameObject* obj4 = AddObject(new Block(Dirt));
		//obj4->Position(Vector2(Graphics::SCREEN_WIDTH - 400, Graphics::SCREEN_HEIGHT - 400));


		GameObject* world = AddObject(new World());

		//GameObject* block = AddObject(new Block(Dirt));
		//block->Position(Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT));
	}
};

class BlockScene : public Scene
{
public:
	BlockScene()
	{
		activeCamera = new WASDCamera();
		GameObject* world = AddObject(new World());
	}
};