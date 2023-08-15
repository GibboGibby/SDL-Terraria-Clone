#include "Scene.h"
#include "Graphics.h"

Scene::Scene()
{
	activeCamera = new Camera();
	//Start();
}

Scene::~Scene()
{
	/*
	for (GameObject* obj : gameObjects)
	{
			delete obj;
	}
	*/

	for (int i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}
	gameObjects.clear();
}

void Scene::ClearScene()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		delete gameObjects[i];
	}
	gameObjects.clear();
}

void Scene::Awake()
{
	for (GameObject* obj : gameObjects)
	{
		obj->Awake();
	}
	activeCamera->Start();
}

void Scene::Start()
{
	for (GameObject* obj : gameObjects)
	{
		obj->Start();
	}
}


void Scene::Update()
{
	for (GameObject* obj : gameObjects)
	{
		obj->Update();
	}
	if (activeCamera != NULL)
		activeCamera->Update();
}

void Scene::UpdateTextures()
{
	for (GameObject* obj : gameObjects)
	{
		obj->UpdateTexture();
	}
}

void Scene::PhysicsUpdate()
{

}

void Scene::Render()
{
	for (GameObject* obj : gameObjects)
	{
		obj->Render();
	}
}

GameObject* Scene::AddObject(GameObject* obj)
{
	gameObjects.push_back(obj);
	return obj;
}

Camera* Scene::GetActiveCamera()
{
	return activeCamera;
}

Vector2 Scene::ScreenToWorldPosition(Vector2 pos)
{
	if (activeCamera == nullptr)
		return pos;
	else
		return pos + activeCamera->Position(GameObject::WORLD);
}

Vector2 Scene::WorldToScreenPosition(Vector2 pos)
{
	if (activeCamera == nullptr)
		return pos;
	else
		return pos - activeCamera->Position(GameObject::WORLD);
}

GameObject* Scene::FindObjectWithName(std::string name)
{
	for (GameObject* obj : gameObjects)
	{
		if (obj->Name() == name) return obj;
	}
	printf("No object found with that name");
	return NULL;
}