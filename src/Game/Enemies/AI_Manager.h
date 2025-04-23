#pragma once
#include "Engine/Core/GameObject.h"
#include "Engine/Core/ObjectPooler.h"
#include "Game/Enemies/BasicEnemy.h"

#include "Game/Enemies/CollectorEnemy.h"

class AI_Manager : public GameObject {

public:
	AI_Manager();

	virtual void Init(Object* OwningObject) override;
	//virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	//virtual void BeginPlay() override;
	//virtual void Update() override;
	virtual void FixedUpdate(float deltaTime) override;
	//virtual void Render(sf::RenderWindow& Renderer) override;
	//virtual void OnDestroy() override;


protected:
	void Handle_CrystalAppeared(GameObject* Crystal);
	void TargetPlayer(Enemy* EnemyToTarget);
	ObjectPooler<CollectorEnemy>* m_Collectors = nullptr;
};