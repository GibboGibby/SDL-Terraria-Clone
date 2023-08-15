#pragma once
#include <string>
#include <vector>
#include "Camera.h"

class Scene
{
protected:
	std::string name;
	int id;

	std::vector<GameObject*> gameObjects;

	Camera* activeCamera;

public:
	GameObject* FindObjectWithTag(std::string tag);
	GameObject* FindObjectWithName(std::string tag);
	GameObject* AddObject(GameObject* obj);
	Camera* GetActiveCamera();


	void ClearScene();
	
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void UpdateTextures();
	virtual void PhysicsUpdate();
	virtual void Render();

	Vector2 WorldToScreenPosition(Vector2 pos);

	Vector2 ScreenToWorldPosition(Vector2 pos);

	Scene();
	~Scene();
};