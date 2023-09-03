#pragma once
#include "Camera.h"

class WASDCamera : public Camera
{
public:

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Render();

private:
	float moveSpeed = 2500;
};