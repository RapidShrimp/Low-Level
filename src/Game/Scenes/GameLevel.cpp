#pragma once
#include "GameLevel.h"
#include "Engine/Core/ObjectPooler.h"
#include "Game/Player/PlayerCharacter.h"
#include "Game/Pickups/Crystal.h"
#include "Game/Enemies/CollectorEnemy.h"
#include "Game/Projectiles/Projectile.h"
#include "Game/Misc/AsteroidManager.h"

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
	SpawnObject(new CollectorEnemy(), Math::Vector2(50,50), true, "Enemy1");
	m_AsteroidManager = new AsteroidManager();
	SpawnObject(m_AsteroidManager,Math::Vector2::Zero(),true,"AsteroidManager");
	SpawnObject(new Asteroid(), Math::Vector2(400, 10), true, "AsteroidTest");
	m_CollectorPooler = new ObjectPooler<CollectorEnemy>(1, false);
	m_BulletPooler = new ObjectPooler<Projectile>(15, false);
	//m_EnemyPooler = new ObjectPooler<Enemy>(3, false);

}
