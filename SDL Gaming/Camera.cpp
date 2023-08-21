#include "Camera.h"
#include "SceneManager.h"

Camera::Camera()
{
	mPos.x = Graphics::SCREEN_WIDTH / 2;
	mPos.y = Graphics::SCREEN_HEIGHT / 2;


}

Camera::~Camera()
{

}

void Camera::Start()
{
	
}

void Camera::Update()
{
	if (Input->GetKeyDown(SDL_SCANCODE_P))
	{
		printf("P has been pressed\n");
	}

	//printf("Value of mouse wheel scrolled is %s\n", (Input->GetMouseScrolled()) ? "true" : "false");
	//printf("Value of the mouse wheel delta is x - %i and y - %i\n", Input->MouseWheelDelta(InputManager::MWHEEL_LEFT_RIGHT), Input->MouseWheelDelta());
	if (Input->GetMouseScrolled())
	{
		printf("mouse has been scrolled but the camera version\n");
		int mouseScroll = Input->MouseWheelDelta();
		tempVal += (0.15f * mouseScroll);
		SceneManager::Instance()->GetScene()->ScaleObjects(tempVal);
	}
}

void Camera::Render()
{

}

Vector2 Camera::GetBounds()
{
	return cameraBounds;
}

float Camera::CameraScale()
{
	return cameraScale;
}

void Camera::Awake()
{
	
}

