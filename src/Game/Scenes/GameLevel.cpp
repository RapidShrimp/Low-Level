#pragma once
#include "GameLevel.h"
#include "Game/Player/PlayerCharacter.h"

void GameLevel::LoadScene()
{
	m_Player = new PlayerCharacter();
	SpawnObject(m_Player, Math::Vector2(100, 100),true,"Player");
}
