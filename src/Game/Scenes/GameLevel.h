#pragma once
#include "Engine/Core/GameScene.h"
#include "Engine/Core/ObjectPooler.h"



class PlayerCharacter;
class CollectorEnemy;
class Projectile;
class AsteroidManager;

class GameLevel : public GameScene 
{
protected:
	PlayerCharacter* m_Player = nullptr;
public:

	GameLevel();
	void OnLoadScene() override;

	ObjectPooler<CollectorEnemy>* m_CollectorPooler = nullptr;
	ObjectPooler<Projectile>* m_BulletPooler = nullptr;
	AsteroidManager* m_AsteroidManager = nullptr;

	virtual PlayerCharacter* GetPlayerCharacter() override { return m_Player; }
};