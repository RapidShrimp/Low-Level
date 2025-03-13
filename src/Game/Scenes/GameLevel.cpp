#pragma once
#include "GameLevel.h"
#include "Game/Player/PlayerCharacter.h"

GameLevel::GameLevel()
{
	m_SceneName = "Game Level";
}

void GameLevel::OnLoadScene()
{
	GameScene::OnLoadScene();
	m_Player = new PlayerCharacter();
	SpawnObject(m_Player, Math::Vector2(250,250),true,"Player");
}
