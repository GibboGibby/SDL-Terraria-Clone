#pragma once
#include "SDL.h"
#include "MathsHelper.h"
#include "Input.h"
#include "Timer.h"
#include <string>
#define Input InputManager::Instance()
#define deltaTime Timer::Instance()->DeltaTime()
#define fixedDeltaTime Timer::Instance()->PhysicsDeltaTime()

class GameObject 
{
public:
	enum SPACE {LOCAL = 0, WORLD = 1};

private:

	bool mActive;
	GameObject* mParent;

protected:
	float mRotation;
	Vector2 mPos;
	Vector2 screenPos;
	int mWidth;
	int mHeight;
	Vector2 mScale;

	std::string name;
	std::string tag;

public:
	GameObject(float x = 0.0f, float y = 0.0f);
	GameObject(Vector2 pos);
	~GameObject();

	void Position(Vector2 pos);
	Vector2 Position(SPACE space = WORLD);
	
	void ScreenPos(Vector2 pos);
	Vector2 ScreenPos();
	void Rotation(float rotation);
	float Rotation(SPACE space = WORLD);

	void Scale(Vector2 scale);
	Vector2 Scale(SPACE space = WORLD);

	void Active(bool active);
	bool Active();

	void Parent(GameObject* parent);
	GameObject* Parent();

	void Translate(Vector2 vec);

	void Name(std::string _name)
	{
		name = _name;
	}
	std::string Name()
	{
		return name;
	}

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void FixedUpdate();
	virtual void LateUpdate();
	virtual void UpdateTexture();
	virtual void Render();

	float GetWidth()
	{
		return (float)mWidth;
	}
	float GetHeight()
	{
		return (float)mHeight;
	}


};