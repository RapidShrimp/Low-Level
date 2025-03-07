#pragma once
#include "GameScene.h"
#include <iostream>

GameScene::GameScene()
{

}

GameScene::~GameScene()
{
	
}

void GameScene::RegisterSpawnedObject(Object* RegisterObject)
{

	//Find if an instance already exists in the registered scene objects
	if (std::find(SceneObjects.begin(), SceneObjects.end(), RegisterObject) != SceneObjects.end())
	{
		cout << "Warning: Object Already Registered, avoid calling SpawnObject() more than once" << endl;
		return;
	}
	SceneObjects.push_back(RegisterObject);
	RegisterObject->Init(this);
	RegisterObject->BeginPlay();
}

GameObject* GameScene::SpawnObject(GameObject* Spawnable, SinStr::Transform SpawnTransform)
{
	Spawnable->m_Transform = SpawnTransform;
	RegisterSpawnedObject(Spawnable);
	return Spawnable;
}

GameObject* GameScene::SpawnObject(GameObject* Spawnable, Math::Vector2 SpawnLocation)
{
	Spawnable->m_Transform.Location = SpawnLocation;
	return SpawnObject(Spawnable, SinStr::Transform(SpawnLocation));
}

void GameScene::RenderScene(sf::RenderWindow& Renderer)
{
	for (int Objects = 0; Objects < SceneObjects.size(); Objects++) 
	{
		SceneObjects[Objects]->Render(Renderer);
	}

}

void GameScene::Update()
{
	for (int Objects = 0; Objects < SceneObjects.size(); Objects++)
	{
		SceneObjects[Objects]->Update();
	}
}

void GameScene::LoadScene()
{
	//Create Game Objects Here
	//Example:
	/*
	GameObject* GreenCircle = new GameObject();
	RegisterSpawnedObject(GreenCircle);
	*/
}

void GameScene::UnloadScene()
{
	for (int i = 0; i < SceneObjects.size(); i++) 
	{
		SceneObjects[i]->OnDestroy();
		delete SceneObjects[i];
	}
}
