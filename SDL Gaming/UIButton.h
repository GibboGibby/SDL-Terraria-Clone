#pragma once
#include "UIElement.h"
#include "SceneManager.h"
class UIButton : public UIElement
{
public:
	UIButton(std::string file) : UIElement(file) {}

	virtual void Update();
	virtual void OnButtonClicked();
	virtual void Render();


};

class CustomButton : public UIButton
{
public:
	CustomButton() : UIButton("BasicButton.png") {}

	void OnButtonClicked()
	{
		printf("This actually worked\n");
		SceneManager::Instance()->ChangeScene(SceneManager::SCENE_MAIN_GAME);
		//GameManager::Instance()->Quit();
	}
};