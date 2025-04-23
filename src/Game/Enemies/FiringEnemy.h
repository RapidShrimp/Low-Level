#pragma once

#include "BasicEnemy.h"

class FiringEnemy : public Enemy 
{

public:
	FiringEnemy();
	virtual void BeginPlay() override;
	virtual void OnActivate() override;
	virtual void AI_Logic(float DeltaTime) override;
	virtual void Handle_EnemyDeath() override;
	void FireWeapon();
};