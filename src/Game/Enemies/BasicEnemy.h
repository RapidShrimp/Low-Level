#pragma once
#include "Engine/Core/GameObject.h"
#include "Engine/Core/Components/SpriteRenderer.h"
#include "Engine/Core/Components/Rigidbody.h"
#include "Game/Components/HealthComponent.h"
#include "Engine/Core/AI/SteeringManager.h"

class Enemy : public GameObject 
{
protected:
	HealthComponent* m_Health;
	SpriteRenderer* m_SpriteRenderer;
	Rigidbody* m_RigidBody;
	Collider* m_Collider;
	SteeringManager* m_SteeringManager;
	float m_MoveSpeed = 0.003f;

	GameObject* m_Target = nullptr;
	float m_KeepDistance = 10.0f;

public:

	SinStr::Event<>OnEnemyDeath;

	Enemy();
	~Enemy() {};
	virtual void Init(Object* OwningObject) override;
	//virtual void OnActivate() override;
	//virtual void OnDeactivate() override;
	virtual void BeginPlay() override;
	virtual void Update() override;
	virtual void FixedUpdate(float DeltaTime) override;
	virtual void OnDestroy() override;
	virtual void SetNewTarget(GameObject* NewTarget);
	SteeringManager* GetSteering() { return m_SteeringManager; }


protected:
	virtual void Handle_EnemyDeath();
	virtual void AI_Logic(float DeltaTime);
private:

};