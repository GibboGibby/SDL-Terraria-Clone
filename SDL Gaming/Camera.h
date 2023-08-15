#pragma once
#include "GameObject.h"
#include "Graphics.h"
#include "MathsHelper.h"

class Camera : public GameObject
{
private:
	int viewHalfHeight;
	int viewHalfWidth;

	GameObject* character;
public:
	Camera();
	~Camera();
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Render();

	void SetMC(GameObject* obj)
	{
		character = obj;
	}

	

};