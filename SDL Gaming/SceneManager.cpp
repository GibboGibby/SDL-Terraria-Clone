#include "SceneManager.h"
#include "Scenes.h"
#include <vector>
SceneManager* SceneManager::instance = NULL;

SceneManager* SceneManager::Instance()
{
	if (instance == NULL)
		instance = new SceneManager();
	return instance;
}

void SceneManager::Release()
{
	delete instance;
	instance = NULL;

}

Scene* SceneManager::GetScene()
{
	return currentScene;
}

void SceneManager::ChangeScene(SCENES scene)
{
	//currentScene->ClearScene();
	delete currentScene;
	currentScene = NULL;
	switch (scene)
	{
	case SCENE_MAIN_MENU:
		currentScene = new TextScene();
		break;
	case SCENE_MAIN_GAME:
		currentScene = new DuckScene();
		break;
	case SCENE_OPTIONS:
		break;
	case SCENE_THING:
		break;
	case SCENE_TESTING:
		currentScene = new BlockScene();
	}
}

SceneManager::SceneManager()
{
	//delete currentScene;
	currentScene = new TextScene();
}

SceneManager::~SceneManager()
{
	delete currentScene;
	currentScene = NULL;
}

