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
	m_AsteroidManager = new AsteroidManager();
	m_BulletPooler = new ObjectPooler<Projectile>(15, false);
	
	SpawnObject(m_Player, Math::Vector2(400,400),true,"Player");
	SpawnObject(m_AsteroidManager,Math::Vector2::Zero(),true,"Asteroid Manager");
	SpawnObject(new AI_Manager(), Math::Vector2(50,50), true, "Enemy Manager");
	SpawnObject(new Boss(), Math::Vector2(500, 500), true, "Sinistar Boss");

	m_BombPooler = new ObjectPooler<Sinibomb>(5, false);
	//TODO - m_EnemyPooler = new ObjectPooler<Enemy>(3, false);

 	AudioManger::PlayMusic("sinistar_BuildingTheme.mp3",true);
}
