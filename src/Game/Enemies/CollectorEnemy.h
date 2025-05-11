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

	//virtual void BeginPlay() override;
	virtual void Init(Object* OwningObject) override;
	virtual void AI_Logic(float DeltaTime) override;
	virtual void Handle_EnemyDeath() override; 
	void CollectCrystal(Crystal* InCrystal);
	void TargetCrystal(Crystal* InCrystal);
	virtual void SetNewTarget(GameObject* NewTarget) override;
	virtual void OnDestroy() override;

protected:
	void Handle_CrystalLost(GameObject* Collided);
};