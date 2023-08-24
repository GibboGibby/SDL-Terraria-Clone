#include "GameObject.h"

GameObject::GameObject(float x, float y)
{
	mPos.x = x - mWidth / 2;
	mPos.y = y - mHeight / 2;

	screenPos = mPos;

	mRotation = 0.0f;

	mActive = true;

	mParent = NULL;

	mScale = VEC2_ONE;
}

GameObject::GameObject(Vector2 pos)
{
	mPos.x = pos.x - mWidth / 2;
	mPos.y = pos.y - mHeight / 2;

	screenPos = mPos;

	mRotation = 0.0f;

	mActive = true;

	mParent = NULL;

	mScale = VEC2_ONE;
}

GameObject::~GameObject()
{
	mParent = NULL;
}

void GameObject::Position(Vector2 pos)
{
	mPos = pos;
}

Vector2 GameObject::Position(SPACE space)
{
	if (space == LOCAL || mParent == NULL)
		return mPos;

	Vector2 parentScale = mParent->Scale(WORLD);
	Vector2 rotPos = RotateVector(mPos, mParent->Rotation(LOCAL));

	return mParent->Position(WORLD) + Vector2(rotPos.x * parentScale.x, rotPos.y * parentScale.y);
}

void GameObject::ScreenPos(Vector2 pos)
{
	screenPos = pos;
}

Vector2 GameObject::ScreenPos()
{
	return screenPos;
}

void GameObject::Scale(Vector2 scale)
{
	mScale = scale;
	if (mScale.x < 0) mScale.x = 0;
	if (mScale.y < 0) mScale.y = 0;
}

Vector2 GameObject::Scale(SPACE space)
{
	if (space == LOCAL || mParent == NULL)
		return mScale;
	Vector2 parentScale = mParent->Scale(WORLD);

	return Vector2(parentScale.x * mScale.x, parentScale.y * mScale.y);
}

void GameObject::Rotation(float r)
{
	mRotation = r;
	if (mRotation > 360.0f)
		mRotation -= 360.0f;

	if (mRotation < 0.0f)
		mRotation += 360.0f;
}

float GameObject::Rotation(SPACE space)
{
	if (space == LOCAL || mParent == NULL)
		return mRotation;

	return mParent->Rotation(WORLD) + mRotation;
}

void GameObject::Active(bool active)
{
	mActive = active;
}

bool GameObject::Active()
{
	return mActive;
}

void GameObject::Parent(GameObject* parent)
{
	mPos = Position(WORLD) - parent->Position(WORLD);

	mParent = parent;
}

GameObject* GameObject::Parent()
{
	return mParent;
}

void GameObject::Awake()
{

}

void GameObject::Start()
{

}

void GameObject::Update()
{

}

void GameObject::Render()
{

}

void GameObject::LateUpdate()
{
}

void GameObject::Translate(Vector2 vec)
{
	mPos += vec;
}

void GameObject::UpdateTexture()
{

}

void GameObject::FixedUpdate()
{
}
