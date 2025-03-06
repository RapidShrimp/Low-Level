#pragma once
#include "GameObject.h"
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
	SceneObjects.push_back(RegisterObject);
	RegisterObject->Init();
	RegisterObject->BeginPlay();
}

void GameScene::RenderScene(RenderWindow& Renderer)
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
	GameObject* GreenCircle = new GameObject();
	RegisterSpawnedObject(GreenCircle);
}

void GameScene::UnloadScene()
{
	
}
