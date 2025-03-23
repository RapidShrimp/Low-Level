#pragma once
#include "GameLevel.h"
#include "Game/Player/PlayerCharacter.h"
#include "Game/Enemies/BasicEnemy.h"
#include "Game/Misc/Asteroid.h"

GameLevel::GameLevel()
{
	m_SceneName = "Game Level";
	SetName("Game Level 1");
}

void GameLevel::OnLoadScene()
{
	GameScene::OnLoadScene();
	m_Player = new PlayerCharacter();
	SpawnObject(m_Player, Math::Vector2(400,400),true,"Player");
	SpawnObject(new Enemy(), Math::Vector2(50,50), true, "Enemy1");
	SpawnObject(new Asteroid(), Math::Vector2(400, 10), true, "AsteroidTest");
}
