#pragma once
#include "GameLevel.h"
#include "Game/Player/PlayerCharacter.h"
#include "Game/Enemies/BasicEnemy.h"

GameLevel::GameLevel()
{
	m_SceneName = "Game Level";
	SetName("Game Level 1");
}

void GameLevel::OnLoadScene()
{
	GameScene::OnLoadScene();
	m_Player = new PlayerCharacter();
	SpawnObject(m_Player, Math::Vector2(250,250),true,"Player");
	SpawnObject(new Enemy(), Math::Vector2(400, 400), true, "Enemy1");
}
