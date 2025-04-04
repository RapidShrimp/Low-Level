#pragma once
#include "Engine/Core/GameScene.h"
#include "Engine/Core/ObjectPooler.h"
#include "Game/Projectiles/Projectile.h"
#include "Game/Misc/Asteroid.h"


class PlayerCharacter;

class GameLevel : public GameScene 
{
protected:
	PlayerCharacter* m_Player = nullptr;
public:

	GameLevel();
	void OnLoadScene() override;

	ObjectPooler<Projectile>* m_BulletPooler = nullptr;
	ObjectPooler<Asteroid>* m_AsteroidPooler = nullptr;

	virtual const PlayerCharacter* GetPlayerCharacter() override { return m_Player; }
};