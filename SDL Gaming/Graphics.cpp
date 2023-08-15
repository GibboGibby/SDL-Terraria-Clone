#include "Graphics.h"
#include "GameManager.h"

Graphics* Graphics::instance = NULL;

bool Graphics::initialized = false;

Graphics* Graphics::Instance()
{
	if (instance == NULL)
		instance = new Graphics();

	return instance;
}

void Graphics::Release()
{
	delete instance;
	instance = NULL;

	initialized = false;
}

bool Graphics::Initialized()
{
	return initialized;
}

Graphics::Graphics()
{
	mBackBuffer = NULL;
	initialized = Init();
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyRenderer(mRenderer);
	mRenderer = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Graphics::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL Initialisation error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("Game!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		printf("Window creation error: %s\n", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (mRenderer == NULL)
	{
		printf("Window creation error :%s\n", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);

	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) * flags))
	{
		printf("IMG Initialisation Error: %s\n", IMG_GetError());
		return false;
	}
	
	if (TTF_Init() == -1)
	{
		printf("TTF Initialisation error: %s\n", TTF_GetError());
		return false;
	}

	mBackBuffer = SDL_GetWindowSurface(window);

	return true;
}

SDL_Texture* Graphics::LoadTexture(std::string path)
{
	SDL_Texture* tex = NULL;

	SDL_Surface* surface = IMG_Load(path.c_str());

	if (surface == NULL) {
		printf("Image load error: Path(%s)  -  Error(%s)\n", path.c_str(), IMG_GetError());
		return tex;
	}

	tex = SDL_CreateTextureFromSurface(mRenderer, surface);
	if (tex == NULL)
	{
		printf("Create Texture Error: %s\n", SDL_GetError());
		return tex;
	}

	SDL_FreeSurface(surface);

	return tex;
}

void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture* tex,SDL_Rect* clip, SDL_Rect* rend, double ang, SDL_Point* center, SDL_RendererFlip flip)
{
	if ((rend->x < Graphics::SCREEN_WIDTH + rend->w + camOffset && rend->x + (rend->w * 2.f) > 0.0f - camOffset) && (rend->y < Graphics::SCREEN_HEIGHT + (rend->h * 2.0f) + camOffset && rend->y + (rend->h * 2.0f) > 0.0f - camOffset))
	{
		
		SDL_RenderCopyEx(mRenderer, tex, clip, rend, ang, center, flip);
#if _DEBUG
		if (GameManager::Instance()->isDebug)
		{
			SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
			SDL_RenderDrawRect(mRenderer, rend);
			SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
		}
#endif
	}
}

void Graphics::DrawObjectGizmo(Vector2 screenPos)
{
#if _DEBUG
	if (GameManager::Instance()->isDebug)
	{
		SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
		SDL_RenderDrawLine(mRenderer, screenPos.x, screenPos.y, screenPos.x, screenPos.y - 15);
		SDL_SetRenderDrawColor(mRenderer, 0, 255, 0, 255);
		SDL_RenderDrawLine(mRenderer, screenPos.x, screenPos.y, screenPos.x + 15, screenPos.y);
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	}
#endif
}

SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (surface == NULL)
	{
		printf("Text render error: %s\n", TTF_GetError());
		return NULL;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);
	if (tex == NULL)
	{
		printf("Text Texture Creation Error: %s\n", SDL_GetError());
		return NULL;
	}

	SDL_FreeSurface(surface);
	return tex;
}

int Graphics::SetViewport(const SDL_Rect* rect = NULL)
{
	return SDL_RenderSetViewport(mRenderer, rect);
}

//void Graphics::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend)
//{
//	SDL_RenderCopy(mRenderer, tex, clip, rend);
//}

void Graphics::Render()
{
	SDL_RenderPresent(mRenderer);
}