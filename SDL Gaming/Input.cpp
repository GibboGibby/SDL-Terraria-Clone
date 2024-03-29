#include "Input.h"
#include "SceneManager.h"
#include <iostream>


InputManager* InputManager::instance = NULL;

InputManager* InputManager::Instance()
{
	if (instance == NULL)
	{
		instance = new InputManager();
	}


	return instance;
}


void InputManager::Release() {

	delete instance;
	instance = NULL;
}

InputManager::InputManager()
{
	mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
	mPrevKeyboardState = new Uint8[mKeyLength];
	memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
}

InputManager::~InputManager()
{
	delete[] mPrevKeyboardState;
	mPrevKeyboardState = NULL;
}

bool InputManager::GetKey(SDL_Scancode scanCode)
{
	return mKeyboardState[scanCode];
}
bool InputManager::GetKeyDown(SDL_Scancode scanCode)
{
	return mKeyboardState[scanCode] && !mPrevKeyboardState[scanCode];
}
bool InputManager::GetKeyUp(SDL_Scancode scanCode)
{
	return !mKeyboardState[scanCode] && mPrevKeyboardState[scanCode];
}

Uint32 InputManager::MouseMask(MOUSE_BUTTON button)
{
	Uint32 mask = 0;

	switch (button)
	{
	case LEFT:
		mask = SDL_BUTTON_LMASK;
		break;
	case RIGHT:
		mask = SDL_BUTTON_RMASK;
		break;
	case MIDDLE:
		mask = SDL_BUTTON_MMASK;
		break;
	case BACK:
		mask = SDL_BUTTON_X1MASK;
		break;
	case FORWARD:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return mask;
}

bool InputManager::GetMouseButton(MOUSE_BUTTON button)
{
	return (mMouseState & MouseMask(button));
}


bool InputManager::GetMouseButtonDown(MOUSE_BUTTON button)
{
	Uint32 mask = MouseMask(button);
	return (!(mPrevMouseState & mask) && mMouseState & mask);
}
bool InputManager::GetMouseButtonUp(MOUSE_BUTTON button)
{
	Uint32 mask = MouseMask(button);
	return ((mPrevMouseState & mask) && !(mMouseState & mask));
}

Vector2 InputManager::GetMousePos()
{
	//Add code to convert the postiion to a screen position
	return Vector2((float)mMouseX, (float)mMouseY);
}

void InputManager::UpdatePrevInput()
{
	memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
	mPrevMouseState = mMouseState;
}

void InputManager::Update() 
{
	mMouseState = SDL_GetMouseState(&mMouseX, &mMouseY);
}