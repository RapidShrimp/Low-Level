#pragma once
#include "GameLevel.h"
#include "Engine/Core/AudioManager.h"
#include "Engine/Core/ObjectPooler.h"
#include "Game/Player/PlayerCharacter.h"
#include "Game/Pickups/Crystal.h"
#include "Game/Enemies/AI_Manager.h"
#include "Game/Projectiles/Projectile.h"
#include "Game/Projectiles/Sinibomb.h"
#include "Game/Misc/AsteroidManager.h"
#include "Game/Enemies/Boss.h"

GameLevel::GameLevel()
{
	m_SceneName = "Game Level";
	SetName("Game Level 1");
}

void GameLevel::OnLoadScene()
{
	GameScene::OnLoadScene();
	m_Player = new PlayerCharacter();
	m_Player->OnPlayerLostLife.AddListener(this, std::bind(&GameLevel::Handle_PrepareLevel, this, std::placeholders::_1));
	m_Boss = new Boss();
	m_AsteroidManager = new AsteroidManager();
	m_BulletPooler = new ObjectPooler<Projectile>(15, false);
	m_BombPooler = new ObjectPooler<Sinibomb>(5, false);
	
	SpawnObject(m_Player, Math::Vector2(400,400),true,"Player");
	SpawnObject(m_AsteroidManager,Math::Vector2::Zero(),true,"Asteroid Manager");

	m_AgentManager = new AI_Manager();
	SpawnObject(m_AgentManager, Math::Vector2(50,50), true, "Enemy Manager");
	SpawnObject(m_Boss, Math::Vector2(500, 500), true, "Sinistar Boss");

 	AudioManger::PlayMusic("sinistar_BuildingTheme.mp3",true);
}

void GameLevel::UnloadScene()
{

	GameScene::UnloadScene();
	m_Player = nullptr;
	m_Boss = nullptr;
	m_AsteroidManager = nullptr;
	m_BulletPooler = nullptr;
	m_BombPooler = nullptr;
	m_AgentManager = nullptr;
}

void GameLevel::Handle_PrepareLevel(float NewLives)
{
	GameInstance::GetWorld()->GetPlayerCharacter()->ResetPlayer();
	m_AgentManager->ResetAgents();
}
