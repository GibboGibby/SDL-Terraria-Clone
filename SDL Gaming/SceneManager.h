#pragma once
#include "Scene.h"



class SceneManager
{
public:
	enum SCENES
	{
		SCENE_MAIN_MENU,
		SCENE_MAIN_GAME,
		SCENE_OPTIONS,
		SCENE_THING
	};
private:
	static SceneManager* instance;
	Scene* currentScene;

public:

	static SceneManager* Instance();
	static void Release();

	Scene* GetScene();
	void ChangeScene(SCENES scene);

	GameObject* AddObject(GameObject* obj);


private:
	SceneManager();
	~SceneManager();
};