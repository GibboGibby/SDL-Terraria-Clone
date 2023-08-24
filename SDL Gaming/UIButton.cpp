#include "UIButton.h"

void UIButton::Update()
{
	if (Input->GetMouseButtonDown(InputManager::LEFT))
	{
		float topLeftPosX = mRenderRect.x;
		float topLeftPosY = mRenderRect.y;
		Vector2 mousePos = Input->GetMousePos();
		if (mousePos.x > topLeftPosX && mousePos.x < topLeftPosX + ScaledDimensions().x &&
			mousePos.y > topLeftPosY && mousePos.y < topLeftPosY + ScaledDimensions().y)
		{
			OnButtonClicked();
		}
	}
}

void UIButton::Render()
{
	Sprite::Render();
}

void UIButton::OnButtonClicked()
{

}