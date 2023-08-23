#pragma once
#include "GameObject.h"
#include "Graphics.h"
#include "MathsHelper.h"

class Camera : public GameObject
{
public:
	enum CameraMultipliers {
		OneX = 1,
		TwoX,
		ThreeX,
		FourX
	};

private:
	Vector2 cameraBounds;

	float cameraScale = 1.0f;
	float tempVal = 1.0f;

	CameraMultipliers cameraMultiplier;

	GameObject* character;
public:
	Camera();
	~Camera();
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Render();


	Vector2 GetBounds();
	float CameraScale();

	void SetMC(GameObject* obj)
	{
		character = obj;
	}

	

};