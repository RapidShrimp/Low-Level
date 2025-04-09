#pragma once
#include "GameLevel.h"
#include "Engine/Core/ObjectPooler.h"
#include "Game/Player/PlayerCharacter.h"
#include "Game/Enemies/CollectorEnemy.h"
#include "Game/Projectiles/Projectile.h"
#include "Game/Misc/Asteroid.h"
#include "Game/Pickups/Crystal.h"

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
	SpawnObject(new Asteroid(), Math::Vector2(400, 10), true, "AsteroidTest");

	m_BulletPooler = new ObjectPooler<Projectile>(15, false);
;	m_AsteroidPooler = new ObjectPooler<Asteroid>(10, false);
	//m_EnemyPooler = new ObjectPooler<Enemy>(3, false);

}
