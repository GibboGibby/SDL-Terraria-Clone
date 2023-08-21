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

	Sint32 mMouseWheelX;
	Sint32 mMouseWheelY;

	bool mouseWheelScrolled;

public:

	enum MOUSE_BUTTON {LEFT = 0, RIGHT, MIDDLE, BACK, FORWARD};
	enum MOUSE_WHEEL {MWHEEL_UP_DOWN = 0, MWHEEL_LEFT_RIGHT};
	
	InputManager();
	~InputManager();
	static InputManager* Instance();
	static void Release();

	void Update();
	void UpdatePrevInput();

	void SetMouseWheel(const Sint32& x, const Sint32& y);
	void UpdateMouseWheel();
	void ResetMouseWheel();

	int MouseWheelDelta(MOUSE_WHEEL mouseWheel = MWHEEL_UP_DOWN);
	bool GetMouseScrolled();

	bool GetKeyDown(SDL_Scancode scanCode);
	bool GetKey(SDL_Scancode scanCode);
	bool GetKeyUp(SDL_Scancode scanCode);

	bool GetMouseButton(MOUSE_BUTTON button);
	bool GetMouseButtonDown(MOUSE_BUTTON button);
	bool GetMouseButtonUp(MOUSE_BUTTON button);

	Uint32 MouseMask(MOUSE_BUTTON button);

	Vector2 GetMousePos();


};