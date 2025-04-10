#pragma once
#include "BasicEnemy.h"

class CollectorEnemy : public Enemy {

public:


	float m_SweepDelayTime = 120.0f;
	float m_CurrentDelayTime = 121.0f;

	virtual void AI_Logic(float DeltaTime) override;
	virtual void Handle_EnemyDeath() override; 
};