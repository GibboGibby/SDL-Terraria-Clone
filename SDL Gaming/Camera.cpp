#include "Camera.h"
#include "SceneManager.h"

Camera::Camera()
{
	mPos.x = Graphics::SCREEN_WIDTH / 2;
	mPos.y = Graphics::SCREEN_HEIGHT / 2;

	cameraMultiplier = OneX;
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
		//SceneManager::Instance()->GetScene()->
		Graphics::Instance()->ScaleRenderer(2.f, 2.f);
	}

	if (Input->GetKeyDown(SDL_SCANCODE_O))
		Graphics::Instance()->ScaleRenderer(1.f, 1.f);

	if (Input->GetKeyDown(SDL_SCANCODE_I))
		Graphics::Instance()->ScaleRenderer(0.5f, 0.5f);

	if (Input->GetKeyDown(SDL_SCANCODE_U))
		Graphics::Instance()->ScaleRenderer(1.f, -1.f);

	/*
	// Attempting to do some kind of camera zoom but Im not sure
	// Think I have to take the camera into perspective and calculate the objects new position based on the camera.
	if (Input->GetMouseScrolled())
	{
		int mouseScroll = Input->MouseWheelDelta();
		cameraMultiplier = static_cast<CameraMultipliers>(static_cast<int>(cameraMultiplier) + mouseScroll);
		SceneManager::Instance()->GetScene()->ScaleObjects((mouseScroll < 0) ? 0.5f : 2);
	}
	*/
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

