#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include "MathsHelper.h"


class Graphics {
public:
	static const int SCREEN_WIDTH = 1920;
	static const int SCREEN_HEIGHT = 1080;

private:

	const float camOffset = 10.f;
	static Graphics* instance;
	static bool initialized;

	SDL_Window* window;
	SDL_Surface* mBackBuffer;

	SDL_Renderer* mRenderer;

public:

	static Graphics* Instance();
	static void Release();
	static bool Initialized();

	SDL_Texture* LoadTexture(std::string path);
	SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);

	int SetViewport(const SDL_Rect* rect);

	void ClearBackBuffer();

	void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, double angle = 0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//void DrawTexture(SDL_Texture* tex,SDL_Rect* clip = NULL, SDL_Rect* rend = NULL);
	void DrawObjectGizmo(Vector2 screenPos);

	void Render();


private:

	Graphics();
	~Graphics();
	bool Init();
};