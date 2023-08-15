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
		//obj->Scale(Vector2(1.0f, 1.0f));

		GameObject* obj2 = AddObject(new Sprite("DuckSheet2.png", 1, 1, 13, 14));
		obj2->Position(Vector2(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT));
		obj2->Name("Main Character2");

		GameObject* obj3 = AddObject(new Sprite("DuckSheet2.png", 1, 1, 13, 14));
		
		obj3->Position(Vector2(Graphics::SCREEN_WIDTH + 100, Graphics::SCREEN_HEIGHT));
		obj3->Parent(obj2);

		GameObject* obj4 = AddObject(new Sprite("DuckSheet2.png", 1, 1, 13, 14));

		obj4->Position(Vector2(Graphics::SCREEN_WIDTH + 100, Graphics::SCREEN_HEIGHT + 100));
	}
};