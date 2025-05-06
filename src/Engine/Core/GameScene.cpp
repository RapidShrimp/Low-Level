#pragma once
#include "GameScene.h"
#include "Game/Player/PlayerCharacter.h"
#include <iostream>

GameScene::GameScene()
{
	m_SceneName = "Unassigned";

}

GameScene::~GameScene()
{
	
}

void GameScene::RegisterSpawnedObject(GameObject* RegisterObject, bool Activate)
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

	if (Activate) { RegisterObject->Activate(); }
	else { RegisterObject->Deactivate(); }
}

UI_Base* GameScene::SpawnUILayer(UI_Base* Spawnable, SinStr::Transform UI_Transform, bool StartEnabled)
{

	if (std::find(UI_Elements.begin(), UI_Elements.end(), Spawnable) != UI_Elements.end())
	{
		cout << "Warning: UI Element Already Registered, avoid calling SpawnUIElement() more than once" << endl;
		return nullptr;
	}
	UI_Elements.push_back(Spawnable);

	//Initialise GameObject
	Spawnable->Init(this);

	if (StartEnabled) { Spawnable->Activate(); }
	else { Spawnable->Deactivate(); }

	return Spawnable;
}

UI_Base* GameScene::SpawnUILayer(UI_Base* Spawnable, Math::Vector2 UI_Location, bool StartEnabled)
{
	Spawnable->m_Transform.Location = UI_Location;
	return SpawnUILayer(Spawnable,SinStr::Transform(UI_Location),StartEnabled);
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

void GameScene::RenderUI(sf::RenderWindow& Renderer)
{
	//Swap this for a stack style rendering?
	for (int Layer = 0; Layer < UI_Elements.size(); Layer++)
	{
		UI_Elements[Layer]->Render(Renderer);
	}
}

void GameScene::FixedUpdate(float DeltaTime)
{
	if (m_GamePaused) { return; }
	for (int Objects = 0; Objects < SceneObjects.size(); Objects++)
	{
		SceneObjects[Objects]->FixedUpdate(DeltaTime);
	}
}

void GameScene::Update()
{
	if (m_GamePaused) { return; }
	for (int Objects = 0; Objects < SceneObjects.size(); Objects++)
	{
		SceneObjects[Objects]->Update();
	}
}

void GameScene::OnLoadScene()
{
	cout << "Loading Scene: " + m_SceneName << endl;
	//Create Game Objects Here
	//Example:
	/*
	GameObject* GreenCircle = new GameObject();
	RegisterSpawnedObject(GreenCircle);
	*/
}

void GameScene::OnSceneLoaded()
{
	for (int i = 0; i < SceneObjects.size(); i++)
	{
		SceneObjects[i]->BeginPlay();
	}
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

