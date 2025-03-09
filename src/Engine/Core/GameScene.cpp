#pragma once
#include "GameScene.h"
#include <iostream>

GameScene::GameScene()
{
	m_SceneName = "Unassigned";

}

GameScene::~GameScene()
{
	
}

void GameScene::RegisterSpawnedObject(Object* RegisterObject, bool Activate)
{

	//Find if an instance already exists in the registered scene objects
	if (std::find(SceneObjects.begin(), SceneObjects.end(), RegisterObject) != SceneObjects.end())
	{
		cout << "Warning: Object Already Registered, avoid calling SpawnObject() more than once" << endl;
		return;
	}
	SceneObjects.push_back(RegisterObject);

	//Initialise GameObject
	RegisterObject->Init(this);
	RegisterObject->BeginPlay();

	if (Activate) { RegisterObject->Activate(); }
}

GameObject* GameScene::SpawnObject(GameObject* Spawnable, SinStr::Transform SpawnTransform, bool StartActive, std::string DisplayName)
{
	Spawnable->m_Transform = SpawnTransform;
	Spawnable->SetName(DisplayName);
	RegisterSpawnedObject(Spawnable,StartActive);
	return Spawnable;
}

GameObject* GameScene::SpawnObject(GameObject* Spawnable, Math::Vector2 SpawnLocation, bool StartActive, std::string DisplayName)
{
	Spawnable->m_Transform.Location = SpawnLocation;
	return SpawnObject(Spawnable, SinStr::Transform(SpawnLocation), StartActive ,DisplayName);
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

void GameScene::OnLoadScene()
{
	cout << "Loading Scene:" + m_SceneName << endl;
	//Create Game Objects Here
	//Example:
	/*
	GameObject* GreenCircle = new GameObject();
	RegisterSpawnedObject(GreenCircle);
	*/
}

void GameScene::UnloadScene()
{
	cout << "Unloading Scene: " + m_SceneName << endl;
	for (int i = 0; i < SceneObjects.size(); i++) 
	{
		SceneObjects[i]->OnDestroy();
		delete SceneObjects[i];
	}
}
