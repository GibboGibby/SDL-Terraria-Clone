#pragma once
#include <SDL.h>
#include "MathsHelper.h"

class InputManager {
private:
	static InputManager* instance;
	Uint8* mPrevKeyboardState;
	const Uint8* mKeyboardState;
	int mKeyLength;

	Uint32 mPrevMouseState;
	Uint32 mMouseState;

	int mMouseX;
	int mMouseY;

public:

	enum MOUSE_BUTTON {LEFT = 0, RIGHT, MIDDLE, BACK, FORWARD};

	InputManager();
	~InputManager();
	static InputManager* Instance();
	static void Release();

	void Update();
	void UpdatePrevInput();

	bool GetKeyDown(SDL_Scancode scanCode);
	bool GetKey(SDL_Scancode scanCode);
	bool GetKeyUp(SDL_Scancode scanCode);

	bool GetMouseButton(MOUSE_BUTTON button);
	bool GetMouseButtonDown(MOUSE_BUTTON button);
	bool GetMouseButtonUp(MOUSE_BUTTON button);

	Uint32 MouseMask(MOUSE_BUTTON button);

	Vector2 GetMousePos();

};