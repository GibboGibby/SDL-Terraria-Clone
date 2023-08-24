#pragma once
#include "Sprite.h"

class UIElement : public Sprite
{
public:
	UIElement(std::string text, std::string fontPath, int size, SDL_Color color) :
		Sprite(text, fontPath, size, color) {}

	UIElement(std::string file) : Sprite(file) {}

	UIElement(std::string file, int x, int y, int w, int h);

	virtual void Update();
	virtual void Render();
};