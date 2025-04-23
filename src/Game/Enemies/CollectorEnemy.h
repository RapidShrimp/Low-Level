#pragma once
#include "BasicEnemy.h"
class Crystal;


class CollectorEnemy : public Enemy {


protected:
	Crystal* m_HeldCrystal = nullptr;
public:

	CollectorEnemy();

	float m_SweepDelayTime = 120.0f;
	float m_CurrentDelayTime = 121.0f;


	virtual void AI_Logic(float DeltaTime) override;
	virtual void Handle_EnemyDeath() override; 
	void CollectCrystal(Crystal* InCrystal);
	void TargetCrystal(Crystal* InCrystal);
	
protected:
	void Handle_CrystalLost(GameObject* Collided);
};