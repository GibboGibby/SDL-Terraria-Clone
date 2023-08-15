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

	if (Input->GetKeyDown(SDL_SCANCODE_Z))
	{
		character = SceneManager::Instance()->GetScene()->FindObjectWithName("Main Character2");
	}

	if (character == NULL) return;
	

	mPos = character->Position() - Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2);

}

void Camera::Render()
{

}

void Camera::Awake()
{
	
}

