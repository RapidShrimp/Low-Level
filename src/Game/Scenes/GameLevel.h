#pragma once
#include "Engine/Core/GameScene.h"
#include "Engine/Core/ObjectPooler.h"




class PlayerCharacter;
class CollectorEnemy;
class Projectile;
class Sinibomb;
class AsteroidManager;

class GameLevel : public GameScene 
{
protected:
	PlayerCharacter* m_Player = nullptr;
public:

	GameLevel();
	void OnLoadScene() override;

	ObjectPooler<Projectile>* m_BulletPooler = nullptr;
	ObjectPooler<Sinibomb>* m_BombPooler = nullptr;

	AsteroidManager* m_AsteroidManager = nullptr;
	
	virtual PlayerCharacter* GetPlayerCharacter() override { return m_Player; }
};