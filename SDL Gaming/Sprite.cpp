#include "Sprite.h"

Sprite::Sprite(std::string file)
{
	
	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetTexture(file);


	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mClipped = false;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Sprite::Sprite(std::string file, int x, int y, int w, int h, int custX, int custY)
{
	mGraphics = Graphics::Instance();
	mTimer = Timer::Instance();
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

	mAnimations["idle"] = new Animation(55, 1, 1.15f, 3, LOOP, VERTICAL);
	mAnimations["walking"] = new Animation(1, 1, 0.6f, 4, LOOP, HORIZONTAL);

	if (custX != 0 || custY != 0)
	{
		customCenter = true;
		centerPos = new SDL_Point();
		centerPos->x = custX;
		centerPos->y = custY;
	}


	currentAnimation = mAnimations["idle"];
	//mTex = new AnimatedTexture("DuckSheet2.png", 1, 1, 13, 14, 4,0.5f,AnimatedTexture::HORIZONTAL);
}

Sprite::Sprite(std::string text, std::string fontPath, int size, SDL_Color color)
{
	mGraphics = Graphics::Instance();

	mTimer = Timer::Instance();
	
	mTex = AssetManager::Instance()->GetText(text, fontPath, size, color);

	mClipped = false;

	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Sprite::~Sprite()
{
	mTex = NULL;
	mGraphics = NULL;
	delete centerPos;
	centerPos = NULL;
}

void Sprite::Update()
{
	if (Input->GetKey(SDL_SCANCODE_D) && (Name() == "Main Character" || Name() == "Main Character2"))
	{
		Translate(Vector2(100.f, 0.f) * deltaTime);
	}
}

void Sprite::Render()
{
	//Vector2 pos = Position(WORLD);
	Vector2 pos = CurrentScene->WorldToScreenPosition(Position(WORLD));

	Vector2 scale = Scale(WORLD);

	//int newX = (pos.x + mWidth / 2) - (mWidth / 2 * mRenderScale);
	//int newY = (pos.y + mHeight / 2) - (mHeight / 2 * mRenderScale);
	mRenderRect = { 0, 0, (int)(mWidth * scale.x), (int)(mHeight * scale.y) };


	//mRenderRect.x -= mWidth / 2;
	//mRenderRect.y += mHeight / 2;
	
	mRenderRect.x = pos.x - (int)(mWidth * scale.x) / 2;
	mRenderRect.y = pos.y - (int)(mHeight * scale.y) / 2;

	//mRenderRect.x = pos.x;
	//mRenderRect.y = pos.y;
	
	//Vector2 worldPos = Position();
	//mRenderRect.x = worldPos.x;
	//mRenderRect.y = worldPos.y;

	mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD), (customCenter) ? centerPos : NULL, (spriteFlipped) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
	mGraphics->DrawObjectGizmo(pos);
}

void Sprite::UpdateTexture()
{
	if (currentAnimation == NULL) return;
	mAnimationTimer += mTimer->DeltaTime();
	if (mAnimationTimer >= currentAnimation->AnimationSpeed)
	{
		if (currentAnimation->WrapMode == LOOP)
		{
			mAnimationTimer -= currentAnimation->AnimationSpeed;
		}
		else
		{
			mAnimationTimer = currentAnimation->AnimationSpeed - currentAnimation->TimePerFrame;
			currentAnimation = prevAnimation;
		}
	}

	if (currentAnimation->AnimDir == HORIZONTAL)
	{
		mClipRect.y = currentAnimation->StartY;
		mClipRect.x = currentAnimation->StartX + (int)(mAnimationTimer / currentAnimation->TimePerFrame) * mWidth;
	}
	else
	{
		mClipRect.x = currentAnimation->StartX;
		mClipRect.y = currentAnimation->StartY + (int)(mAnimationTimer / currentAnimation->TimePerFrame) * mHeight;
	}

}

void Sprite::ChangeAnimation(std::string animName)
{
	prevAnimation = currentAnimation;
	currentAnimation = mAnimations[animName];
	mAnimationTimer = 0.0f;
	//printf("Animation has been changed\n");
}

std::string Sprite::GetCurrentAnimation()
{
	for (auto& i : mAnimations)
	{
		if (i.second == currentAnimation)
			return i.first;
	}
	return "";
}

Vector2 Sprite::ScaledDimensions()
{
	Vector2 scaledDimensions = Scale();
	scaledDimensions.x *= mWidth;
	scaledDimensions.y *= mHeight;

	return scaledDimensions;
}