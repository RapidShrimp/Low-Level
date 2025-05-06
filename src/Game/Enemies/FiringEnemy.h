#pragma once

#include "BasicEnemy.h"
#include "Engine/Core/Timer.h"
class FiringEnemy : public Enemy 
{
protected:
	Timer* m_FiringTimer;
public:
	FiringEnemy();
	void Init(Object* OwningObject) override;
	virtual void BeginPlay() override;
	virtual void OnActivate() override;
	virtual void AI_Logic(float DeltaTime) override;
	virtual void Handle_EnemyDeath() override;
	void FireWeapon();
};