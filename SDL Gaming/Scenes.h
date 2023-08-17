#pragma once
#include "Scene.h"
#include "Sprite.h"
#include "Texture.h"
#include "Duck.h"

class TextScene : public Scene
{
public:
	TextScene() : Scene()
	{
		GameObject* obj = AddObject(new Sprite("New Gaming!", "stocky.ttf", 72, { 0, 0, 255 }));
		obj->Position(Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT));
		obj->Name("Main Character");
	}
};

class DuckScene : public Scene
{
public:
	DuckScene()
	{
		//delete activeCamera;
		//activeCamera = NULL;
		GameObject* obj = AddObject(new MainDuck());
		obj->Position(Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT));
		obj->Name("Main Character");

		GameObject* obj2 = AddObject(new MainDuck(true));
		obj2->Position(Vector2(Graphics::SCREEN_WIDTH + 200, Graphics::SCREEN_HEIGHT + 200));
		obj2->Name("Main Character Enemy");
	}
};