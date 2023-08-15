#pragma once
#include "GameObject.h"
#include "AssetManager.h"
#include "AudioManager.h"

class Texture : public GameObject
{
protected:
	SDL_Texture* mTex;

	Graphics* mGraphics;

	bool mClipped;
	SDL_Rect mClipRect;

	SDL_Rect mRenderRect;


public:
	Texture(std::string file);
	Texture(std::string file, int x, int y, int w, int h);
	Texture(std::string text, std::string fontPath, int size, SDL_Color color);
	~Texture();

	virtual void Update();
	virtual void Render();


};