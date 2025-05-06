#pragma once
#include "Game/Enemies/BasicEnemy.h"
#include "Engine/Core/Timer.h"
class Crystal; 

class Boss : public Enemy {

protected:
	bool m_Created = false;
	int m_Pieces = 0;
	Timer* m_AttackTimer;
	Timer* m_MovePause;

	Math::Vector2 m_AttackDirection;
public:

	SinStr::Event<int> OnPeicesUpdated;

	Boss();

	virtual void Init(Object* OwningObject) override;
	//virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	virtual void BeginPlay() override;
	virtual void Update() override;
	virtual void FixedUpdate(float DeltaTime) override;
	virtual void OnDestroy() override;
	virtual void Render(sf::RenderWindow& Renderer) override;
	inline bool IsCreated() { return m_Created; }
	void GiveCrystal(Crystal* InPeice);
	
protected:

	void ChargePlayer();
	void StopMoving();
	virtual void Handle_TakeDamage(float Damage);
	virtual void Handle_EnemyDeath();
	virtual void AI_Logic(float DeltaTime);



};