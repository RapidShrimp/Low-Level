#pragma once
#include "Engine/Core/GameScene.h"
#include "Engine/Core/ObjectPooler.h"




class PlayerCharacter;
class CollectorEnemy;
class Projectile;
class Sinibomb;
class AsteroidManager;
class Boss;
class AI_Manager;

class GameLevel : public GameScene 
{
protected:
	PlayerCharacter* m_Player = nullptr;
	Boss* m_Boss = nullptr;

public:

	GameLevel();
	void OnLoadScene() override;
	void UnloadScene() override;
	ObjectPooler<Projectile>* m_BulletPooler = nullptr;
	ObjectPooler<Sinibomb>* m_BombPooler = nullptr;
	AsteroidManager* m_AsteroidManager = nullptr;
	AI_Manager* m_AgentManager = nullptr;
	virtual PlayerCharacter* GetPlayerCharacter() override { return m_Player; }
	virtual Boss* GetSinistarBoss() { return m_Boss; }


private:
	void Handle_PrepareLevel(float NewLives);
};