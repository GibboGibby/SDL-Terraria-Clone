#include "Texture.h"


Texture::Texture(std::string file)
{
	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetTexture(file);

	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mClipped = false;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::Texture(std::string file, int x, int y, int w, int h)
{
	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetTexture(file);

	mClipped = true;

	mWidth = w;
	mHeight = h;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mClipRect.x = x;
	mClipRect.y = y;
	mClipRect.w = mWidth;
	mClipRect.h = mHeight;
}

Texture::Texture(std::string text, std::string fontPath, int size, SDL_Color color)
{
	mGraphics = Graphics::Instance();
	mTex = AssetManager::Instance()->GetText(text, fontPath, size, color);

	mClipped = false;

	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}



Texture::~Texture()
{
	mTex = NULL;
	mGraphics = NULL;
}

float renderScalar = 1.f;

void Texture::Render()
{
	Vector2 pos = Position(WORLD);
	//mRenderRect.x = (int)(pos.x - (mWidth * 0.5f));
	//mRenderRect.y = (int)(pos.y - (mHeight * 0.5f));

	int newX = (pos.x + mWidth / 2) - (mWidth / 2 * renderScalar);
	int newY = (pos.y + mHeight / 2) - (mHeight / 2 * renderScalar);
	mRenderRect = { newX, newY, (int)(mWidth * renderScalar), (int)(mHeight * renderScalar) };

	mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect);
}

void Texture::Update()
{
	if (Input->GetMouseButton(InputManager::LEFT))
	{
		Position(Input->GetMousePos());
	}

	if (Input->GetKey(SDL_SCANCODE_A))
		Translate(Vector2(-100.f, 0.f) * deltaTime);
	if (Input->GetKey(SDL_SCANCODE_D))
		Translate(Vector2(100.f, 0.f) * deltaTime);
	if (Input->GetKey(SDL_SCANCODE_W))
		Translate(Vector2(0.f, -100.f) * deltaTime);
	if (Input->GetKey(SDL_SCANCODE_S))
		Translate(Vector2(0.f, 100.f) * deltaTime);

	if (Input->GetKeyDown(SDL_SCANCODE_O))
	{
		renderScalar -= 0.5f;
	}

	if (Input->GetKeyDown(SDL_SCANCODE_P))
	{
		renderScalar += 2.f;
	}

	
}
